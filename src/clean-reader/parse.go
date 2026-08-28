package main

import (
	"fmt"
	"io"
	"os"
	"regexp"

	"golang.org/x/net/html"
)

type Parser struct{}

var dataPattern *regexp.Regexp = nil

func pruneAttributes(input []html.Attribute) []html.Attribute {
	if dataPattern == nil {
		var err error
		dataPattern, err = regexp.Compile("^data-")
		if err != nil {
			panic(err)
		}
	}
	var out []html.Attribute
	for _, attr := range input {
		if dataPattern.Match([]byte(attr.Key)) {
			continue
		}
		if attr.Key == "style" {
			continue
		}
		//if attr.Key == "class" {
		//	continue
		//}
		//if attr.Key == "id" {
		//	continue
		//}
		//fmt.Printf("%s\n", attr.Key)
		out = append(out, attr)
	}
	return out
}

func (p Parser) clone(node, parent, prevSibling *html.Node) *html.Node {
	var firstChild, lastChild *html.Node
	children := p.parseChildren(node)
	if len(children) >= 1 {
		firstChild = children[0]
	}
	if len(children) > 1 {
		lastChild = children[len(children)-1]
	}

	var attributes = pruneAttributes(node.Attr)
	return &html.Node{
		Parent:      parent,
		FirstChild:  firstChild,
		LastChild:   lastChild,
		PrevSibling: prevSibling,

		Type:      node.Type,
		DataAtom:  node.DataAtom,
		Data:      node.Data,
		Namespace: node.Namespace,
		Attr:      attributes,
	}
}

// TODO: should only be called from clone
func (p *Parser) parseChildren(node *html.Node) []*html.Node {
	var childClones []*html.Node
	var cur, prev *html.Node
	for child := range node.ChildNodes() {
		prev = cur
		cur = p.parseNode(child, node, prev)
		if cur == nil {
			cur = prev
			continue
		}
		childClones = append(childClones, cur)
		if prev != nil {
			prev.NextSibling = cur
		}
	}

	return childClones
}

func (p *Parser) parseElement(node, parent, prevSibling *html.Node) *html.Node {
	switch node.DataAtom.String() {
	// skip
	case "button":
		fallthrough
	case "figcaption":
		fallthrough
	case "footer":
		fallthrough
	case "form":
		fallthrough
	case "header":
		fallthrough
	case "head":
		fallthrough
	case "img":
		fallthrough
	case "script":
		fallthrough
	case "svg":
		return nil

	// recurse into
	case "a":
		fallthrough
	case "br":
		fallthrough
	case "div":
		fallthrough
	case "em":
		fallthrough
	case "figure":
		fallthrough
	case "h1":
		fallthrough
	case "h2":
		fallthrough
	case "h3":
		fallthrough
	case "h4":
		fallthrough
	case "h5":
		fallthrough
	case "h6":
		fallthrough
	case "html":
		fallthrough
	case "li":
		fallthrough
	case "main":
		fallthrough
	case "p":
		fallthrough
	case "span":
		fallthrough
	case "strong":
		fallthrough
	case "time":
		fallthrough
	case "ul":
		fallthrough
	case "body":
		return p.clone(node, parent, prevSibling)

	// Unimplemented
	default:
		// TODO panic
		fmt.Fprintf(os.Stderr, "Unimplemented ElementNode type (%s): %s\n", node.DataAtom.String(), node.Data)
		os.Exit(1)
	}
	panic("unreachable")
}

func (p *Parser) parseNode(node, parent, prevSibling *html.Node) *html.Node {
	switch node.Type {
	case html.ErrorNode:
		panic(*node)
	case html.TextNode:
		return p.clone(node, parent, prevSibling)
	case html.DocumentNode:
		return p.clone(node, parent, prevSibling)
	case html.ElementNode:
		return p.parseElement(node, parent, prevSibling)
	case html.CommentNode:
		fallthrough
	case html.DoctypeNode:
		return nil
	default:
		panic("Unimplemented")
	}
}

type Roots struct {
	Title string
	Body *html.Node
}

func findRoots(node *html.Node) Roots {
	var roots Roots
	for cur := range node.Descendants() {
		var eitherSet = false
		atomString := cur.DataAtom.String()
		if cur.Type == html.ElementNode && atomString == "body" {
			roots.Body = cur
			eitherSet = true
		} else if cur.Type == html.ElementNode && atomString == "title" {
			for child := range cur.ChildNodes() {
				if child.Type == html.TextNode {
					roots.Title = child.Data
					break
				}
			}
			if roots.Title == "" {
				panic("Huh?")
			}
			eitherSet = true
		}
		if eitherSet && roots.Body != nil && roots.Title != "" {
			return roots
		}
	}
	if roots.Body == nil {
		panic("\"body\" not found!")
	}
	return roots
}

func parse(reader io.Reader) Roots {
	root, err := html.Parse(reader)
	if err != nil {
		panic(err)
	}
	roots := findRoots(root)
	var p Parser
	roots.Body = p.parseNode(roots.Body, nil, nil)
	return roots
}

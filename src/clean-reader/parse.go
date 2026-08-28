package main

import (
	"fmt"
	"io"
	"os"

	"golang.org/x/net/html"
)

type Parser struct{}

func (p Parser) clone(node, parent, prevSibling *html.Node) *html.Node {
	var firstChild, lastChild *html.Node
	children := p.parseChildren(node)
	if len(children) >= 1 {
		firstChild = children[0]
	}
	if len(children) > 1 {
		lastChild = children[len(children)-1]
	}

	return &html.Node{
		Parent:      parent,
		FirstChild:  firstChild,
		LastChild:   lastChild,
		PrevSibling: prevSibling,

		Type:      node.Type,
		DataAtom:  node.DataAtom,
		Data:      node.Data,
		Namespace: node.Namespace,
		Attr:      node.Attr, // safe to share
	}
}

// TODO: should only be called from clone
func (p *Parser) parseChildren(node *html.Node) []*html.Node {
	var childClones []*html.Node
	var cur, prev *html.Node
	for child := range node.ChildNodes() {
		prev = cur
		cur = p.parseNode(child, node, prev)
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

func findMain(node *html.Node) *html.Node {
	for cur := range node.Descendants() {
		if cur.Type == html.ElementNode && cur.DataAtom.String() == "main" {
			return cur
		}
	}
	panic("\"main\" not found!")
}

func parse(reader io.Reader) *html.Node {
	root, err := html.Parse(reader)
	if err != nil {
		panic(err)
	}
	main := findMain(root)
	var p Parser
	return p.parseNode(main, nil, nil)
}

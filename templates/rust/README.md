# Rust

Use `rustup` to bootstrap toolchain:

```sh
sudo apt-get install rustup
```

Set the default install to the latest stable:

```sh
$ rustup default stable
info: syncing channel updates for 'stable-x86_64-unknown-linux-gnu'
info: latest update on 2026-10-15, rust version 1.99.1 (58cf8f9c3 2026-10-13)

  stable-x86_64-unknown-linux-gnu installed - rustc 1.99.1 (58cf8f9c3 2026-10-13)
```

View local docs:

```sh
rustup doc
```

Ensure offline dependencies are cached:

```sh
$ cargo new get-dependencies
$ pushd get-dependencies
$ cargo add rand@0.10.1 trpl@0.2.0
$ popd # get-dependencies
$ rm -rf get-dependencies
```

Install rust-analyzer (an LSP server):

```sh
$ rustup component add rust-analyzer
```

Ensure `nvim` config has (where `on_attach` is a callback setting your key
bindings):

```lua
vim.lsp.enable('rust_analyzer')
vim.lsp.config('rust_analyzer', {
  on_attach = on_attach,
})
```

`rust-analyzer` will only work on Cargo projects, so run:

```sh
$ mkdir foo && cd foo
$ cargo init .
```

## Fullstack Reason Demo

This project shows a minimal fullstack
[ReasonML](https://reasonml.github.io/) application. It has a

- Backend web server that compiles to a native binary using the Esy/dune
  compilation toolchain
- Frontend ReasonReact component that compiles to JavaScript using the
  BuckleScript toolchain
- Shared business logic used by both of the above

This is a proof-of-concept; you can customize it to your needs.

## Try it out

> At the moment unfortunately the backend may not work on Windows due to
> an issue with a dependency. I am trying to resolve it.

Follow these steps:

1. Install [NodeJS](https://nodejs.org/en/) (one-time setup)
1. Install Esy (one-time setup): `npm install --global esy@latest`
1. Set up the backend project: `esy install` (one-time setup but will
   take a while to compile dependencies like SSL so grab your favourite
   beverage)
1. Run the backend app: `esy b dune exec backend/App.exe`
1. In another terminal, build frontend:
   a. `npm install` (or use [pnpm](https://pnpm.js.org/) to save some disk space)
   b. `npx bsb -clean-world`
   c. `npx bsb -make-world`
1. Run the frontend (this is in development mode): `npm run server`
1. Browse the frontend: http://localhost:8000/

### 'Production' mode

You can also try out the app without the Webpack dev server:

1. Assuming the above builds have already been done
1. Put production assets in the `build` directory:
   `npm run webpack:production`
1. Run the backend app: `esy b dune exec backend/App.exe`
1. Browse the frontend (note, different port than above, this is being
   served directly from the backend app): http://localhost:8080/

## How it works

This project pulls together:

- A working setup of the [ReWeb](https://github.com/yawaramin/re-web/)
  Reason/OCaml native web framework
- A [ReasonReact](https://reasonml.github.io/reason-react/) frontend app,
  using the [BuckleScript](https://bucklescript.github.io/) OCaml-to-JS
  compiler

## Project layout

These are the significant parts of the project:

- `backend/`: contains the sources for the backend executable
- `esy.lock/`: a lock directory used by Esy to capture precise dependency
  information
- `frontend/`: contains the sources for the frontend ReasonReact app
- `shared/`: contains sources shared between the backend and frontend
- `bsconfig.json`: BuckleScript project configuration
- `dune-project`: [Dune](https://dune.build/) project configuration (for
  the native build)
- `esy.json`: Esy project configuration (native package management)
- `fullstack-reason.opam`: [OPAM](http://opam.ocaml.org/) project
  configuration (empty but needed for backward-compatibility with OPAM)
- `package.json`: [Npm](https://www.npmjs.com/) project configuration
- `webpack.config.js`: [Webpack](https://webpack.js.org/) bundler
  configuration for the frontend

Honourable mention: build outputs are in the `.gitignore`.

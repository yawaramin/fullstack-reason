module Prometo = Yawaramin__Prometo;

// One-off binding to Fetch API

module Response = {
  type t;
  [@bs.send] external json: t => Js.Promise.t(Js.Json.t);
};

[@bs.val] external fetch: string => Js.Promise.t(Response.t);

// Helpers for the component

let decode = json =>
  switch (Shared.User.t_decode(json)) {
  | Ok(_) as ok => ok
  | Error({Decco.message, _}) => Error(message)
  };

let endpoint = "http://localhost:8080/bob";

// The component

[@react.component]
let make = () => {
  let (user, setUser) = React.useState(() => None);

  React.useEffect0(() => {
    let promise = endpoint
      |> fetch
      |> Prometo.fromPromise
      |> Prometo.thenPromise(~f=Response.json);

    Prometo.forEach(~f=json => setUser(_ => Some(decode(json))), promise);
    Prometo.Error.forEach(~f=_ => setUser(_ => Some(Error("Web request failed!"))), promise);

    Some(() => Prometo.cancel(promise));
  });

  let message =
    React.string(
      switch (user) {
      // Finished loading a user successfully:
      | Some(Ok(user)) => Shared.User.toString(user)
      // Finished the request but failed to load user:
      | Some(Error(message)) => {j|(ERROR) $message|j}
      // Not finished the request yet:
      | None => "(Loading...)"
      },
    );

  <p> message </p>;
};

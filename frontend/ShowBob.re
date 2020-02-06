// One-off binding to Fetch API

module Response = {
  type t;
  [@bs.send] external json: t => Js.Promise.t(Js.Json.t) = "";
};

[@bs.val] external fetch: string => Js.Promise.t(Response.t) = "";

// Helpers for the component

let decode = json =>
  switch (Shared.User.t_decode(json)) {
  | Ok(_) as ok => ok
  | Error({Decco.message, _}) => Error(message)
  };

let setOk = (~setUser, json) =>
  Js.Promise.resolve(setUser(_ => Some(decode(json))));

let setError = (~setUser, _error) =>
  Js.Promise.resolve(setUser(_ => Some(Error("Web request failed!"))));

let endpoint = "http://localhost:8080/bob";

// The component

[@react.component]
let make = () => {
  let (user, setUser) = React.useState(() => None);

  React.useEffect0(() => {
    endpoint
    |> fetch
    |> Js.Promise.then_(Response.json)
    |> Js.Promise.then_(setOk(~setUser))
    |> Js.Promise.catch(setError(~setUser))
    |> ignore;

    None;
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

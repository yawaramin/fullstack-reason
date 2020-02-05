// One-off binding to Fetch API

module Response = {
  type t;
  [@bs.send] external text: t => Js.Promise.t(string) = "";
};

[@bs.val] external fetch: string => Js.Promise.t(Response.t) = "";

// Helpers for the component

let decode = string =>
  switch (Js.Json.parseExn(string)) {
  | json =>
    switch (Shared.User.t_decode(json)) {
    | Ok(_) as ok => ok
    | Error({Decco.message, _}) => Error(message)
    }
  | exception _ => Error("JSON parse failed")
  };

let setOk = (~setUser, string) =>
  Js.Promise.resolve(setUser(_ => Some(decode(string))));

let setError = (~setUser, _error) =>
  Js.Promise.resolve(setUser(_ => Some(Error("(Web request failed!)"))));

let endpoint = "http://localhost:8080/bob";

// The component

[@react.component]
let make = () => {
  let (user, setUser) = React.useState(() => None);

  React.useEffect0(() => {
    endpoint
    |> fetch
    |> Js.Promise.then_(Response.text)
    |> Js.Promise.then_(setOk(~setUser))
    |> Js.Promise.catch(setError(~setUser))
    |> ignore;

    None;
  });

  switch (user) {
  // Finished loading a user successfully:
  | Some(Ok(user)) =>
    // Using shared business logic:
    <> <p> {user |> Shared.User.toString |> React.string} </p> </>
  // Finished the request but failed to load user:
  | Some(Error(message)) => <p> {React.string(message)} </p>
  // Not finished the request yet:
  | None => <p> {React.string("(Loading...)")} </p>
  };
};

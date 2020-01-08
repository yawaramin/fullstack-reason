type t = {
  id: int,
  name: string,
};

let make = (id, name) => {id, name};
let ofString = string => Scanf.sscanf(string, "ID=%d, name=%s", make);
let toString = ({id, name}) => Printf.sprintf("ID=%d, name=%s", id, name);

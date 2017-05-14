type t;

external _navigate :
  Js.t {
    .
    routeName : string, params : Js.Undefined.t (Js.Dict.t string), action : Js.Undefined.t t
  } =>
  t =
  "navigate" [@@bs.scope "NavigationActions"] [@@bs.module "react-navigation"];

let navigate
    routeName::(routeName: string)
    params::(params: option (Js.Dict.t string))=?
    action::(action: option t)=?
    ()
    :t =>
  _navigate {
    "routeName": routeName,
    "params": Js.Undefined.from_opt params,
    "action": Js.Undefined.from_opt action
  };

external _reset : Js.t {. index : int, actions : Js.Undefined.t (array t)} => t =
  "reset" [@@bs.scope "NavigationActions"] [@@bs.module "react-navigation"];

let reset index::(index: int) actions::(actions: option (list t))=? () :t =>
  _reset {
    "index": index,
    "actions": Js.Undefined.from_opt (NavUtils.option_map Array.of_list actions)
  };

external _back : Js.t {. key : Js.Null.t string} => t =
  "back" [@@bs.scope "NavigationActions"] [@@bs.module "react-navigation"];

let back ::key=? () =>
  switch key {
  | Some key => _back {"key": Js.Null.return key}
  | None => _back {"key": Js.Null.empty}
  };

external _setParams : Js.t {. params : Js.Dict.t string, key : string} => t =
  "setParams" [@@bs.scope "NavigationActions"] [@@bs.module "react-navigation"];

let setParams ::params ::key => _setParams {"params": params, "key": key};

external _init : Js.t {. params : Js.Dict.t string} => t =
  "init" [@@bs.scope "NavigationActions"] [@@bs.module "react-navigation"];

let init ::params => _init {"params": params};
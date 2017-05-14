type navigationParams = Js.Dict.t string;

type t;

type state = {
  routeName: string,
  key: string,
  params: navigationParams,
  path: option string,
  index: option int,
  routes: option (array state)
};

type stateJs =
  Js.t {
    .
    key : string,
    routeName : string,
    path : Js.Undefined.t string,
    params : Js.Undefined.t navigationParams,
    index : Js.Undefined.t int,
    routes : Js.Undefined.t (array stateJs)
  };

external _state : t => stateJs = "state" [@@bs.get];

let rec fromJs (js: stateJs) :state => {
  let key = js##key;
  let routeName = js##routeName;
  let params =
    switch (Js.Undefined.to_opt js##params) {
    | Some p => p
    | None => Js.Dict.empty ()
    };
  let path = Js.Undefined.to_opt js##path;
  let index = Js.Undefined.to_opt js##index;
  let routes = Js.Undefined.to_opt js##routes |> NavUtils.option_map (Array.map fromJs);
  {key, routeName, params, path, index, routes}
};

let state t => fromJs (_state t);

external _navigate : t => string => Js.Undefined.t (Js.Dict.t string) => /* TODO action => */ unit =
  "navigate" [@@bs.send];

let navigate t ::routeName ::params=? /* TODO ::action=? */ () =>
  _navigate t routeName (Js.Undefined.from_opt params);

external setParams : t => Js.Dict.t string => unit = "" [@@bs.send];

external _goBack : t => Js.Null_undefined.t string => unit = "goBack" [@@bs.send];

let goBack t from::(from: option [ | `routeKey string | `anywhere])=? () =>
  switch from {
  | Some (`routeKey routeKey) => _goBack t (Js.Null_undefined.return routeKey)
  | Some `anywhere => _goBack t Js.Null_undefined.null
  | _ => _goBack t Js.Null_undefined.undefined
  };

external dispatch : t => NavigationActionsRe.t => unit = "" [@@bs.send];
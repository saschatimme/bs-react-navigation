type t 'params;

type state 'params = {
  routeName: string,
  key: string,
  params: Js.t 'params,
  path: option string,
  index: option int
  /*routes: option (array (state {.}))*/
};

type stateJs 'params =
  Js.t {
    .
    key : string,
    routeName : string,
    path : Js.Undefined.t string,
    params : Js.Undefined.t (Js.t 'params),
    index : Js.Undefined.t int
    /*routes : Js.Undefined.t (array (stateJs {.}))*/
  };

external getState : t 'params => stateJs 'params = "state" [@@bs.get];

/*
 let rec fromJs (js: stateJs 'params) :state 'params => {
   let key = js##key;
   let routeName = js##routeName;
   let params = Js.Undefined.to_opt js##params;
   let path = Js.Undefined.to_opt js##path;
   let index = Js.Undefined.to_opt js##index;
   /*let routes = Js.Undefined.to_opt js##routes |> NavUtils.option_map (Array.map fromJs);*/
   {key, routeName, params, path, index}
 };*/
let state t => {
  let js = getState t;
  let key = js##key;
  let routeName = js##routeName;
  let params =
    switch (Js.Undefined.to_opt js##params) {
    | Some p => p
    | None => Js.Obj.empty ()
    };
  let path = Js.Undefined.to_opt js##path;
  let index = Js.Undefined.to_opt js##index;
  /*let routes = Js.Undefined.to_opt js##routes |> NavUtils.option_map (Array.map fromJs);*/
  {key, routeName, params, path, index}
};

external _navigate :
  t 'params => string => Js.Undefined.t (Js.t 'params) => /* TODO action => */ unit =
  "navigate" [@@bs.send];

let navigate t ::routeName ::params=? /* TODO ::action=? */ () =>
  _navigate t routeName (Js.Undefined.from_opt params);

external setParams : t 'params => Js.t 'params => unit = "" [@@bs.send];

external _goBack : t 'paras => Js.Null_undefined.t string => unit = "goBack" [@@bs.send];

let goBack t from::(from: option [ | `routeKey string | `anywhere])=? () =>
  switch from {
  | Some (`routeKey routeKey) => _goBack t (Js.Null_undefined.return routeKey)
  | Some `anywhere => _goBack t Js.Null_undefined.null
  | _ => _goBack t Js.Null_undefined.undefined
  };

external dispatch : t 'params => NavigationActionsRe.t 'params => unit = "" [@@bs.send];
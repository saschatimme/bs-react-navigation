type headerProps /* TODO */;

type style = ReactNative.Style.t;

module NavigationOptions = {
  type t = {
    title: option string,
    header: option [ | `custom (headerProps => ReasonReact.reactElement) | `notVisible],
    headerTitle: option ReasonReact.reactElement,
    headerTitleStyle: option style,
    headerTintColor: option string,
    headerBackTitle: option string,
    headerTruncatedBackTitle: option string,
    headerLeft: option ReasonReact.reactElement,
    headerBackTitleStyle: option style,
    headerPressColorAndroid: option string,
    headerRight: option ReasonReact.reactElement,
    headerStyle: option style,
    gesturesEnabled: option bool
  };
  type js =
    Js.t {
      .
      title : Js.Undefined.t string,
      header : Js.Null_undefined.t (headerProps => ReasonReact.reactElement),
      headerTitle : Js.Undefined.t ReasonReact.reactElement,
      headerTitleStyle : Js.Undefined.t style,
      headerTintColor : Js.Undefined.t string,
      headerBackTitle : Js.Undefined.t string,
      headerTruncatedBackTitle : Js.Undefined.t string,
      headerLeft : Js.Undefined.t ReasonReact.reactElement,
      headerBackTitleStyle : Js.Undefined.t style,
      headerPressColorAndroid : Js.Undefined.t string,
      headerRight : Js.Undefined.t ReasonReact.reactElement,
      headerStyle : Js.Undefined.t style,
      gesturesEnabled : Js.Undefined.t Js.boolean
    };
  /* for the dynamic nav options later */
  type abstract;
  let fromJs (jsItem: js) :t =>
    Js.Undefined.{
      title: to_opt jsItem##title,
      header:
        if (Js.Null.test (Obj.magic jsItem##header)) {
          Some `notVisible
        } else {
          switch (Js.Null_undefined.to_opt jsItem##header) {
          | Some el => Some (`custom el)
          | None => None
          }
        },
      headerTitle: to_opt jsItem##headerTitle,
      headerTitleStyle: to_opt jsItem##headerTitleStyle,
      headerTintColor: to_opt jsItem##headerTintColor,
      headerBackTitle: to_opt jsItem##headerBackTitle,
      headerTruncatedBackTitle: to_opt jsItem##headerTruncatedBackTitle,
      headerLeft: to_opt jsItem##headerLeft,
      headerBackTitleStyle: to_opt jsItem##headerBackTitleStyle,
      headerPressColorAndroid: to_opt jsItem##headerPressColorAndroid,
      headerRight: to_opt jsItem##headerRight,
      headerStyle: to_opt jsItem##headerStyle,
      gesturesEnabled: NavUtils.option_map Js.to_bool (to_opt jsItem##gesturesEnabled)
    };
  external _makeJs :
    title::string? =>
    header::Js.Null.t (headerProps => ReasonReact.reactElement)? =>
    headerTitle::ReasonReact.reactElement? =>
    headerTitleStyle::style? =>
    headerTintColor::string? =>
    headerBackTitle::string? =>
    headerTruncatedBackTitle::string? =>
    headerLeft::ReasonReact.reactElement? =>
    headerBackTitleStyle::style? =>
    headerPressColorAndroid::string? =>
    headerRight::ReasonReact.reactElement? =>
    headerStyle::style? =>
    gesturesEnabled::Js.boolean? =>
    unit =>
    js =
    "" [@@bs.obj];
  let makeJs
      ::title=?
      ::header=?
      ::headerTitle=?
      ::headerTitleStyle=?
      ::headerTintColor=?
      ::headerBackTitle=?
      ::headerTruncatedBackTitle=?
      ::headerLeft=?
      ::headerBackTitleStyle=?
      ::headerPressColorAndroid=?
      ::headerRight=?
      ::headerStyle=?
      ::gesturesEnabled=?
      ()
      :js =>
    _makeJs
      ::?title
      header::?(
        NavUtils.option_map
          (
            fun
            | `custom el => Js.Null.return el
            | `notVisible => Js.null
          )
          header
      )
      ::?headerTitle
      ::?headerTitleStyle
      ::?headerTintColor
      ::?headerBackTitle
      ::?headerTruncatedBackTitle
      ::?headerLeft
      ::?headerBackTitleStyle
      ::?headerPressColorAndroid
      ::?headerRight
      ::?headerStyle
      gesturesEnabled::?(NavUtils.option_map Js.Boolean.to_js_boolean gesturesEnabled)
      ();
};

type navigationOptions = NavigationOptions.js;

type navigationOptionsRecord = NavigationOptions.t;

module Config = {
  type js 'params =
    Js.t {
      .
      /*router*/
      initialRouteName : Js.Undefined.t string,
      initialRouteParams : Js.t 'params,
      paths : Js.Undefined.t (Js.Dict.t string),
      navigationOptions : Js.Undefined.t NavigationOptions.t,
      /*view*/
      mode : Js.Undefined.t string,
      headerMode : Js.Undefined.t string,
      cardStyle : Js.Undefined.t style,
      /*TODO transitionConfig*/
      onTransitionStart : Js.Undefined.t (unit => unit),
      onTransitionEnd : Js.Undefined.t (unit => unit)
    };
  external makeConfig :
    initialRouteName::string? =>
    initialRouteParams::Js.t 'params? =>
    paths::Js.Dict.t string? =>
    navigationOptions::NavigationOptions.t? =>
    mode::string? =>
    headerMode::string? =>
    cardStyle::style? =>
    onTransitionStart::(unit => unit)? =>
    onTransitionEnd::(unit => unit)? =>
    unit =>
    js 'params =
    "" [@@bs.obj];
  let config
      ::initialRouteName=?
      ::initialRouteParams=?
      ::paths=?
      ::navigationOptions=?
      mode::(mode: option [ | `card | `modal])=?
      headerMode::(headerMode: option [ | `float | `none | `screen])=? => {
    let mode =
      switch mode {
      | Some `card => Some "card"
      | Some `modal => Some "modal"
      | _ => None
      };
    let headerMode =
      switch headerMode {
      | Some `float => Some "float"
      | Some `none => Some "none"
      | Some `screen => Some "screen"
      | _ => None
      };
    makeConfig
      ::?initialRouteName ::?initialRouteParams ::?paths ::?navigationOptions ::?mode ::?headerMode
  };
};

type config 'params = Config.js 'params;

type self 'screenProps 'params = {
  navigation: NavigationRe.t 'params,
  screenProps: 'screenProps,
  navigationOptions: option NavigationOptions.t
};


/** We will make this type abstract */
type selfJs 'screenProps 'params =
  Js.t {
    .
    navigation : NavigationRe.t 'params,
    screenProps : 'screenProps,
    navigationOptions : Js.Undefined.t NavigationOptions.js
  };

module Route = {
  type js 'screenProps 'params =
    Js.t {
      .
      screen : selfJs 'screenProps 'params => ReasonReact.reactElement,
      path : Js.Undefined.t string,
      navigationOptions : Js.Undefined.t NavigationOptions.js
    };
  external makeJs :
    screen::(selfJs 'screenProps 'params => ReasonReact.reactElement) =>
    path::string? =>
    navigationOptions::NavigationOptions.abstract? =>
    unit =>
    js 'screenProps 'params =
    "" [@@bs.obj];
  type navigationOptions 'screenProps 'params = [
    | `static NavigationOptions.js
    | `dynamic (self 'screenProps 'params => NavigationOptions.js)
  ];
  let make
      screen::(screen: self 'screenProps 'params => ReasonReact.reactElement)
      path::(path: option string)=?
      navigationOptions::(navigationOptions: option (navigationOptions 'screenProps 'params))=?
      () =>
    makeJs
      screen::(
        fun (jsItems: selfJs 'screenProps 'params) => {
          let navigation = jsItems##navigation;
          let screenProps = jsItems##screenProps;
          let navigationOptions =
            NavUtils.option_map
              NavigationOptions.fromJs (Js.Undefined.to_opt jsItems##navigationOptions);
          screen {navigation, screenProps, navigationOptions}
        }
      )
      ::?path
      navigationOptions::?(
        switch navigationOptions {
        | Some (`dynamic dynNavOps) =>
          Obj.magic (
            Some (
              fun jsItems =>
                dynNavOps {
                  navigation: jsItems##navigation,
                  screenProps: jsItems##screenProps,
                  navigationOptions:
                    NavUtils.option_map
                      NavigationOptions.fromJs (Js.Undefined.to_opt jsItems##navigationOptions)
                }
            )
          )
        | Some (`static navOps) => Some (Obj.magic navOps)
        | None => None
        }
      )
      ();
};

let navigationOptions = NavigationOptions.makeJs;

let config = Config.config;


/** We will make this types abstract */
type route 'screenProps 'params = Route.js 'screenProps 'params;

let route = Route.make;

type routes 'screenProps 'params = Js.Dict.t (route 'screenProps 'params);

let routes list :routes 'screenProps 'params => Js.Dict.fromList list;

external _StackNavigator :
  routes 'screenProps 'params => Js.Undefined.t (config 'params) => ReasonReact.reactClass =
  "StackNavigator" [@@bs.module "react-navigation"];

type instance = ReasonReact.reactClass;

let create (routes: routes 'screenProps 'params) config => {
  let reactClass = _StackNavigator routes (Js.Undefined.from_opt config);
  fun ::screenProps children =>
    ReasonReact.wrapJsForReason ::reactClass props::{"screenProps": screenProps} children
};
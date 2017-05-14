type headerProps /* TODO */;

type style = ReactNative.Style.t;

module Component = {
  type navigationOptionsRecord = {
    title: option string,
    header: option (headerProps => ReactRe.reactElement),
    headerVisible: option bool,
    headerTitle: option ReactRe.reactElement,
    headerTitleStyle: option style,
    headerTintColor: option string,
    headerBackTitle: option string,
    headerTruncatedBackTitle: option string,
    headerLeft: option ReactRe.reactElement,
    headerBackTitleStyle: option style,
    headerPressColorAndroid: option string,
    headerRight: option ReactRe.reactElement,
    headerStyle: option style,
    gesturesEnabled: option bool
  };
  type screenBag 'screenProps = {
    navigation: NavigationRe.t,
    screenProps: 'screenProps,
    navigationOptions: option navigationOptionsRecord
  };
};


/** We will make this type abstract */
type navigationOptions =
  Js.t {
    .
    title : Js.Undefined.t string,
    header : Js.Null_undefined.t (headerProps => ReactRe.reactElement),
    headerTitle : Js.Undefined.t ReactRe.reactElement,
    headerTitleStyle : Js.Undefined.t style,
    headerTintColor : Js.Undefined.t string,
    headerBackTitle : Js.Undefined.t string,
    headerTruncatedBackTitle : Js.Undefined.t string,
    headerLeft : Js.Undefined.t ReactRe.reactElement,
    headerBackTitleStyle : Js.Undefined.t style,
    headerPressColorAndroid : Js.Undefined.t string,
    headerRight : Js.Undefined.t ReactRe.reactElement,
    headerStyle : Js.Undefined.t style,
    gesturesEnabled : Js.Undefined.t Js.boolean
  };

let navOptionsFromJs jsItem :Component.navigationOptionsRecord =>
  Component.(
    Js.Undefined.{
      title: to_opt jsItem##title,
      header: Js.Null_undefined.to_opt jsItem##header,
      headerVisible: Some (Js.Null.test (Obj.magic jsItem##header)),
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
    }
  );

let navigationOptions
    ::title=?
    ::header=?
    ::headerVisible=?
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
    () => {
  let x: navigationOptions =
    Js.Undefined.(
      {
        "title": from_opt title,
        "header":
          switch headerVisible {
          | Some true => Js.Null_undefined.from_opt header
          | Some false => Js.Null_undefined.null
          | None => Js.Null_undefined.from_opt header
          },
        "headerTitle": from_opt headerTitle,
        "headerTitleStyle": from_opt headerTitleStyle,
        "headerTintColor": from_opt headerTintColor,
        "headerBackTitle": from_opt headerBackTitle,
        "headerTruncatedBackTitle": from_opt headerTruncatedBackTitle,
        "headerLeft": from_opt headerLeft,
        "headerBackTitleStyle": from_opt headerBackTitleStyle,
        "headerPressColorAndroid": from_opt headerPressColorAndroid,
        "headerRight": from_opt headerRight,
        "headerStyle": from_opt headerStyle,
        "gesturesEnabled": from_opt (NavUtils.option_map Js.Boolean.to_js_boolean gesturesEnabled)
      }
    );
  x
};


/**
  *  Problem:
  *  react-navigation handles { a: undefined} differently
  *  than { }. Therefore we cannot use the default way with a Js.t object.
  *  As a solution, we make the type abstract and use `Obj.magic` and a dict.
  *
 */
type config;

/*
 type config =
   Js.t {
     .
     /*router*/
     initialRouteName : Js.Undefined.t string,
     initialRouteParams : Js.Dict.t string,
     paths : Js.Undefined.t (Js.Dict.t string),
     navigationOptions : Js.Undefined.t navigationOptions,
     /*view*/
     mode : Js.Undefined.t string,
     headerMode : Js.Undefined.t string,
     cardStyle : Js.Undefined.t style,
     /*TODO transitionConfig*/
     onTransitionStart : Js.Undefined.t (unit => unit),
     onTransitionEnd : Js.Undefined.t (unit => unit)
   };*/


let config
    ::initialRouteName=?
    ::initialRouteParams=?
    ::paths=?
    ::navigationOptions=?
    ::mode=?
    ::headerMode=?
    ::cardStyle=?
    ::onTransitionStart=?
    ::onTransitionEnd=?
    ()
    :config => {
  let c = Js.Dict.empty ();
  NavUtils.setValue c "initialRouteName" initialRouteName;
  switch initialRouteParams {
  | None => NavUtils.setValue c "initialRouteParams" (Some (Js.Dict.empty ()))
  | _ => NavUtils.setValue c "initialRouteParams" initialRouteParams
  };
  NavUtils.setValue c "paths" paths;
  NavUtils.setValue c "navigationOptions" navigationOptions;
  NavUtils.setValue c "cardStyle" cardStyle;
  NavUtils.setValue c "onTransitionStart" onTransitionStart;
  NavUtils.setValue c "onTransitionEnd" onTransitionEnd;
  NavUtils.setValue
    c
    "mode"
    (
      NavUtils.option_map
        (
          fun prop =>
            switch prop {
            | `card => "card"
            | `modal => "modal"
            }
        )
        mode
    );
  NavUtils.setValue
    c
    "headerMode"
    (
      NavUtils.option_map
        (
          fun prop =>
            switch prop {
            | `float => "float"
            | `screen => "screen"
            | `none => "none"
            }
        )
        headerMode
    );
  Obj.magic c
};

type externalNavigationOptions;

let screenBag navigation screenProps navigationOptions :Component.screenBag 'screenProps =>
  Component.{navigation, screenProps, navigationOptions};


/** We will make this type abstract */
type screenBagJs 'screenProps =
  Js.t {
    .
    navigation : NavigationRe.t,
    screenProps : 'screenProps,
    navigationOptions : Js.Undefined.t navigationOptions
  };


/** We will make this type abstract */
type routeConfig 'screenProps =
  Js.t {
    .
    screen : screenBagJs 'screenProps => ReactRe.reactElement,
    path : Js.Undefined.t string,
    navigationOptions : Js.Undefined.t externalNavigationOptions
  };

type dynamicNavigationOptions 'screenProps = Component.screenBag 'screenProps => navigationOptions;

let routeConfig
    screen::(screen: Component.screenBag 'screenProps => ReactRe.reactElement)
    path::(path: option string)=?
    navigationOptions::(navigationOptions: option navigationOptions)=?
    dynamicNavigationOptions::
      (dynamicNavigationOptions: option (dynamicNavigationOptions 'screenProps))=?
    ()
    :routeConfig 'screenProps => {
  "screen": fun (jsItems: screenBagJs 'screenProps) => {
    let navigation = jsItems##navigation;
    let screenProps = jsItems##screenProps;
    let navigationOptions =
      NavUtils.option_map navOptionsFromJs (Js.Undefined.to_opt jsItems##navigationOptions);
    screen (screenBag navigation screenProps navigationOptions)
  },
  "path": Js.Undefined.from_opt path,
  "navigationOptions":
    switch dynamicNavigationOptions {
    | Some dynNavOps =>
      Obj.magic (
        Js.Undefined.return (
          fun jsItems =>
            dynNavOps (
              screenBag
                jsItems##navigation
                jsItems##screenProps
                (
                  NavUtils.option_map navOptionsFromJs (Js.Undefined.to_opt jsItems##navigationOptions)
                )
            )
        )
      )
    | None => Obj.magic (Js.Undefined.from_opt navigationOptions)
    }
};


/** We will make this type abstract */
type routesConfig 'screenProps = Js.Dict.t (routeConfig 'screenProps);

let routesConfig (routeList: list (string, routeConfig 'screenProps)) :routesConfig 'screenProps =>
  NavUtils.dictFromList routeList;


/** Our interface */
module type StackNavigatorSpec = {
  type screenProps;
  let routes: routesConfig screenProps;
  let config: option config;
};

module CreateComponent (Spec: StackNavigatorSpec) => {
  external _createElement :
    routesConfig Spec.screenProps => Js.Undefined.t config => ReactRe.reactClass =
    "StackNavigator" [@@bs.module "react-navigation"];
  let wrapProps (screenProps: Spec.screenProps) =>
    ReactRe.wrapPropsShamelessly
      (_createElement Spec.routes (Js.Undefined.from_opt Spec.config))
      {"screenProps": screenProps};
};
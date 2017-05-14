type headerProps /* TODO */;

module Component = {
  type navigationOptionsRecord 'style = {
    title: option string,
    header: option (headerProps => ReactRe.reactElement),
    headerVisible: option bool,
    headerTitle: option ReactRe.reactElement,
    headerTitleStyle: option 'style,
    headerTintColor: option string,
    headerBackTitle: option string,
    headerTruncatedBackTitle: option string,
    headerLeft: option ReactRe.reactElement,
    headerBackTitleStyle: option 'style,
    headerPressColorAndroid: option string,
    headerRight: option ReactRe.reactElement,
    headerStyle: option 'style,
    gesturesEnabled: option bool
  };
  type screenBag 'screenProps 'style = {
    navigation: NavigationRe.t,
    screenProps: 'screenProps,
    navigationOptions: option (navigationOptionsRecord 'style)
  };
};


/** We will make this type abstract */
type navigationOptions 'style =
  Js.t {
    .
    title : Js.Undefined.t string,
    header : Js.Null_undefined.t (headerProps => ReactRe.reactElement),
    headerTitle : Js.Undefined.t ReactRe.reactElement,
    headerTitleStyle : Js.Undefined.t 'style,
    headerTintColor : Js.Undefined.t string,
    headerBackTitle : Js.Undefined.t string,
    headerTruncatedBackTitle : Js.Undefined.t string,
    headerLeft : Js.Undefined.t ReactRe.reactElement,
    headerBackTitleStyle : Js.Undefined.t 'style,
    headerPressColorAndroid : Js.Undefined.t string,
    headerRight : Js.Undefined.t ReactRe.reactElement,
    headerStyle : Js.Undefined.t 'style,
    gesturesEnabled : Js.Undefined.t Js.boolean
  };

let navOptionsFromJs jsItem :Component.navigationOptionsRecord 'style =>
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
      gesturesEnabled: Utils.option_map Js.to_bool (to_opt jsItem##gesturesEnabled)
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
  let x: navigationOptions 'style =
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
        "gesturesEnabled": from_opt (Utils.option_map Js.Boolean.to_js_boolean gesturesEnabled)
      }
    );
  x
};


/** We will make this type abstract */
type config 'style =
  Js.t {
    .
    /*router*/
    initialRouteName : Js.Undefined.t string,
    initialRouteParams : Js.Dict.t string,
    paths : Js.Undefined.t (Js.Dict.t string),
    navigationOptions : Js.Undefined.t (navigationOptions 'style),
    /*view*/
    mode : Js.Undefined.t string,
    headerMode : Js.Undefined.t string,
    cardStyle : Js.Undefined.t 'style,
    /*TODO transitionConfig*/
    onTransitionStart : Js.Undefined.t (unit => unit),
    onTransitionEnd : Js.Undefined.t (unit => unit)
  };

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
    :config 'style =>
  Js.Undefined.(
    {
      "initialRouteName": from_opt initialRouteName,
      "initialRouteParams":
        switch initialRouteParams {
        | Some params => params
        | None => Js.Dict.empty ()
        },
      "paths": from_opt paths,
      "navigationOptions": from_opt navigationOptions,
      "mode":
        from_opt (
          Utils.option_map
            (
              fun prop =>
                switch prop {
                | `card => "card"
                | `modal => "modal"
                }
            )
            mode
        ),
      "headerMode":
        from_opt (
          Utils.option_map
            (
              fun prop =>
                switch prop {
                | `float => "float"
                | `screen => "screen"
                | `none => "none"
                }
            )
            headerMode
        ),
      "cardStyle": from_opt cardStyle,
      "onTransitionStart": from_opt onTransitionStart,
      "onTransitionEnd": from_opt onTransitionEnd
    }
  );

type externalNavigationOptions;

let screenBag navigation screenProps navigationOptions :Component.screenBag 'screenProps 'style =>
  Component.{navigation, screenProps, navigationOptions};


/** We will make this type abstract */
type screenBagJs 'screenProps 'style =
  Js.t {
    .
    navigation : NavigationRe.t,
    screenProps : 'screenProps,
    navigationOptions : Js.Undefined.t (navigationOptions 'style)
  };


/** We will make this type abstract */
type routeConfig 'screenProps 'style =
  Js.t {
    .
    screen : screenBagJs 'screenProps 'style => ReactRe.reactElement,
    path : Js.Undefined.t string,
    navigationOptions : Js.Undefined.t externalNavigationOptions
  };

type dynamicNavigationOptions 'screenProps 'style =
  Component.screenBag 'screenProps 'style => navigationOptions 'style;

let routeConfig
    screen::(screen: Component.screenBag 'screenProps 'style => ReactRe.reactElement)
    path::(path: option string)=?
    navigationOptions::(navigationOptions: option (navigationOptions 'style))=?
    dynamicNavigationOptions::
      (dynamicNavigationOptions: option (dynamicNavigationOptions 'screenProps 'style))=?
    ()
    :routeConfig 'screenProps 'style => {
  "screen": fun (jsItems: screenBagJs 'screenProps 'style) => {
    let navigation = jsItems##navigation;
    let screenProps = jsItems##screenProps;
    let navigationOptions =
      Utils.option_map navOptionsFromJs (Js.Undefined.to_opt jsItems##navigationOptions);
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
                  Utils.option_map navOptionsFromJs (Js.Undefined.to_opt jsItems##navigationOptions)
                )
            )
        )
      )
    | None => Obj.magic (Js.Undefined.from_opt navigationOptions)
    }
};


/** We will make this type abstract */
type routesConfig 'screenProps 'style = Js.Dict.t (routeConfig 'screenProps 'style);

let routesConfig
    (routeList: list (string, routeConfig 'screenProps 'style))
    :routesConfig 'screenProps 'style =>
  Utils.dictFromList routeList;


/** Our interface */
module type StackNavigatorSpec = {
  type screenProps;
  type style;
  let routes: routesConfig screenProps style;
  let config: option (config style);
};

module CreateComponent (Spec: StackNavigatorSpec) => {
  external _createElement :
    routesConfig Spec.screenProps Spec.style =>
    Js.Undefined.t (config Spec.style) =>
    ReactRe.reactClass =
    "StackNavigator" [@@bs.module "react-navigation"];
  let wrapProps (screenProps: Spec.screenProps) =>
    ReactRe.wrapPropsShamelessly
      (_createElement Spec.routes (Js.Undefined.from_opt Spec.config))
      {"screenProps": screenProps};
};
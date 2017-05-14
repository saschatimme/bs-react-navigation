type style = ReactNative.Style.t;

module Component = {
  type navigationOptionsRecord = {
    title: option string,
    tabBarVisible: option bool
    /*
     tabBarIcon: option (focused::bool => tintColor::string => ReactRe.reactElement),
     tabBarLabel: option (focused::bool => tintColor::string => ReactRe.reactElement)*/
  };
  type screenBag 'screenProps = {
    navigation: NavigationRe.t,
    screenProps: 'screenProps,
    navigationOptions: option navigationOptionsRecord
  };
};

type navigationOptions =
  Js.t {
    .
    title : Js.Undefined.t string,
    tabBarVisible : Js.Undefined.t Js.boolean,
    tabBarIcon :
      Js.Undefined.t (Js.t {. focused : Js.boolean, tintColor : string} => ReactRe.reactElement),
    tabBarLabel :
      Js.Undefined.t (Js.t {. focused : Js.boolean, tintColor : string} => ReactRe.reactElement)
  };

type tabBarElement = [
  | `static ReactRe.reactElement
  | `dynamic (focused::bool => tintColor::string => ReactRe.reactElement)
];

let navigationOptions
    title::(title: option string)=?
    tabBarVisible::(tabBarVisible: option bool)=?
    tabBarIcon::(tabBarIcon: option tabBarElement)=?
    tabBarLabel::(tabBarLabel: option tabBarElement)=?
    ()
    :navigationOptions =>
  Js.Undefined.(
    {
      "title": from_opt title,
      "tabBarVisible": from_opt (Utils.option_map Js.Boolean.to_js_boolean tabBarVisible),
      "tabBarIcon":
        from_opt (
          Utils.option_map
            (
              fun p =>
                switch p {
                | `static el => Obj.magic el
                | `dynamic f => (
                    fun js => f focused::(Js.to_bool js##focused) tintColor::js##tintColor
                  )
                }
            )
            tabBarIcon
        ),
      "tabBarLabel":
        from_opt (
          Utils.option_map
            (
              fun p =>
                switch p {
                | `static el => Obj.magic el
                | `dynamic f => (
                    fun js => f focused::(Js.to_bool js##focused) tintColor::js##tintColor
                  )
                }
            )
            tabBarLabel
        )
    }
  );

let navigationOptionsFromJs (jsItem: navigationOptions) :Component.navigationOptionsRecord =>
  Component.(
    Js.Undefined.{
      title: to_opt jsItem##title,
      tabBarVisible: Utils.option_map Js.to_bool (to_opt jsItem##tabBarVisible)
      /** there is no value to provide these values */
      /*tabBarIcon: None,
        tabBarLabel: None*/
    }
  );


/** We will make this type abstract */
type tabBarOptions =
  Js.t {
    .
    /**
     * TabBarTop
     **/
    activeTintColor : Js.Undefined.t string,
    activeBackgroundColor : Js.Undefined.t string,
    inactiveTintColor : Js.Undefined.t string,
    inactiveBackgroundColor : Js.Undefined.t string,
    showLabel : Js.Undefined.t Js.boolean,
    style : Js.Undefined.t style,
    labelStyle : Js.Undefined.t style,
    /**
     *  TabBarBottom
     **/
    /*inactiveTintColor: Js.Undefined.t color,*/
    showIcon : Js.Undefined.t Js.boolean,
    /*showLabel: Js.Undefined.t bool,*/
    upperCaseLabel : Js.Undefined.t Js.boolean,
    pressColor : Js.Undefined.t Js.boolean,
    pressOpacity : Js.Undefined.t float,
    scrollEnabled : Js.Undefined.t Js.boolean,
    tabStyle : Js.Undefined.t style,
    indicatorStyle : Js.Undefined.t style,
    /*style: Js.Undefined.t style,
      labelStyle: Js.Undefined.t style,*/
    iconStyle : Js.Undefined.t style
  };

let tabBarOptions
    ::activeTintColor=?
    ::activeBackgroundColor=?
    ::inactiveTintColor=?
    ::inactiveBackgroundColor=?
    ::showLabel=?
    ::style=?
    ::labelStyle=?
    ::showIcon=?
    ::upperCaseLabel=?
    ::pressColor=?
    ::pressOpacity=?
    ::scrollEnabled=?
    ::tabStyle=?
    ::indicatorStyle=?
    ::iconStyle=?
    ()
    :tabBarOptions =>
  Js.Undefined.(
    {
      "activeTintColor": from_opt activeTintColor,
      "activeBackgroundColor": from_opt activeBackgroundColor,
      "inactiveTintColor": from_opt inactiveTintColor,
      "inactiveBackgroundColor": from_opt inactiveBackgroundColor,
      "showLabel": from_opt (Utils.option_map Js.Boolean.to_js_boolean showLabel),
      "style": from_opt style,
      "labelStyle": from_opt labelStyle,
      "showIcon": from_opt (Utils.option_map Js.Boolean.to_js_boolean showIcon),
      "upperCaseLabel": from_opt (Utils.option_map Js.Boolean.to_js_boolean upperCaseLabel),
      "pressColor": from_opt (Utils.option_map Js.Boolean.to_js_boolean pressColor),
      "pressOpacity": from_opt pressOpacity,
      "scrollEnabled": from_opt (Utils.option_map Js.Boolean.to_js_boolean scrollEnabled),
      "tabStyle": from_opt tabStyle,
      "indicatorStyle": from_opt indicatorStyle,
      "iconStyle": from_opt iconStyle
    }
  );


/** We will make this type abstract */
type config =
  Js.t {
    .
    /*router*/
    initialRouteName : Js.Undefined.t string,
    order : Js.Undefined.t (array string),
    paths : Js.Undefined.t (Js.Dict.t string),
    backBehavior : Js.Undefined.t string,
    /*view*/
    tabBarComponent : Js.Undefined.t ReactRe.reactClass,
    tabBarPosition : Js.Undefined.t string,
    swipeEnabled : Js.Undefined.t Js.boolean,
    animationEnabled : Js.Undefined.t Js.boolean,
    _lazy : Js.Undefined.t Js.boolean,
    tabBarOptions : Js.Undefined.t tabBarOptions
  };

let config
    ::tabBarOptions=?
    ::animationEnabled=?
    ::backBehavior=?
    ::lazy_=?
    ::order=?
    ::swipeEnabled=?
    ::tabBarPosition=?
    ::initialRouteName=?
    ::paths=?
    ::tabBarComponent=?
    ()
    :config =>
  Js.Undefined.(
    {
      "initialRouteName": from_opt initialRouteName,
      "paths": from_opt paths,
      "tabBarOptions": from_opt tabBarOptions,
      "order": from_opt order,
      "_lazy": from_opt (Utils.option_map Js.Boolean.to_js_boolean lazy_),
      "swipeEnabled": from_opt (Utils.option_map Js.Boolean.to_js_boolean swipeEnabled),
      "animationEnabled": from_opt (Utils.option_map Js.Boolean.to_js_boolean animationEnabled),
      "backBehavior":
        from_opt (
          Utils.option_map
            (
              fun prop =>
                switch prop {
                | `none => "none"
                | `initialRoute => "initialRoute"
                }
            )
            backBehavior
        ),
      "tabBarPosition":
        from_opt (
          Utils.option_map
            (
              fun prop =>
                switch prop {
                | `top => "top"
                | `bottom => "bottom"
                }
            )
            tabBarPosition
        ),
      "tabBarComponent": from_opt tabBarComponent
    }
  );


/** We will make this type abstract */
type externalNavigationOptions;

let screenBag navigation screenProps navigationOptions :Component.screenBag 'screenProps =>
  Component.{navigation, screenProps, navigationOptions};

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
      Utils.option_map navigationOptionsFromJs (Js.Undefined.to_opt jsItems##navigationOptions);
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
                  Utils.option_map
                    navigationOptionsFromJs (Js.Undefined.to_opt jsItems##navigationOptions)
                )
            )
        )
      )
    | None => Obj.magic (Js.Undefined.from_opt navigationOptions)
    }
};

type routesConfig 'screenProps = Js.Dict.t (routeConfig 'screenProps);

let routesConfig (routeList: list (string, routeConfig 'screenProps)) :routesConfig 'screenProps =>
  Utils.dictFromList routeList;


/** Our interface */
module type TabNavigatorSpec = {
  type screenProps;
  let routes: routesConfig screenProps;
  let config: option config;
};

module CreateComponent (Spec: TabNavigatorSpec) => {
  external _createElement :
    routesConfig Spec.screenProps => Js.Undefined.t config => ReactRe.reactClass =
    "StackNavigator" [@@bs.module "react-navigation"];
  let wrapProps (screenProps: Spec.screenProps) =>
    ReactRe.wrapPropsShamelessly
      (_createElement Spec.routes (Js.Undefined.from_opt Spec.config))
      {"screenProps": screenProps};
};
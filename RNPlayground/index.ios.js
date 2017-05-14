/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 * @flow
 */

import { comp as App } from "./lib/js/re/app.js";
import React from "react";
import {
  AppRegistry
} from 'react-native';

console.disableYellowBox = true;

AppRegistry.registerComponent('RNPlayground', () => App);

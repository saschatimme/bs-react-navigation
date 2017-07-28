const fs = require("fs-extra");
const path = require("path");

fs.ensureDirSync(path.join(__dirname, "./react-navigation"));
fs.copySync(path.join(__dirname, "../re"), path.join(__dirname, "./react-navigation"));

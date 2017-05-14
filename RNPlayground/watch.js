const chokidar = require("chokidar");
const fs = require("fs");
const path = require("path");

function copyFile(src, dest) {
    let readStream = fs.createReadStream(src);

    readStream.once("error", err => {
        console.log(err);
    });

    readStream.once("end", () => {
        // console.log("done copying");
    });

    readStream.pipe(fs.createWriteStream(dest));
}

function copyReactNavigation() {
    const fileNames = [
        "navigationActionsRe.re",
        "reactNavigation.re",
        "stackNavigatorRe.rei",
        "tabNavigatorRe.rei",
        "navigationRe.re",
        "stackNavigatorRe.re",
        "tabNavigatorRe.re",
        "utils.re"
    ];

    fileNames.forEach (name => {
        copyFile(path.resolve(`../re/${name}`), path.resolve(`./reactNavigation/${name}`));

    }) 
}

const watcher = chokidar.watch("../re/*");

watcher.on("change", () => {
    copyReactNavigation();
});

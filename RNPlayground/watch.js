const chokidar = require("chokidar");
const fs = require("fs");
const path = require("path");

function copyFile(src, dest) {
    let readStream = fs.createReadStream(src);

    readStream.once("error", err => {
        console.log(err);
    });

    readStream.once("end", () => {
        console.log("done copying");
    });

    readStream.pipe(fs.createWriteStream(dest));
}

function copyReactNavigation() {
    const re = "reactNavigation.re";
    const rei = "reactNavigation.rei";

    copyFile(path.resolve(`../re/${re}`), path.resolve(`./reactNavigation/${re}`));
    copyFile(path.resolve(`../re/${rei}`), path.resolve(`./reactNavigation/${rei}`));
}

const watcher = chokidar.watch("../re/*");

watcher.on("change", () => {
    copyReactNavigation();
});

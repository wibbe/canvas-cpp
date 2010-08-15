
function paint() {
   window.log("Paint...");
}

(function() {
   window.log("Starting Demo...");
   window.setInterval(paint);
})();

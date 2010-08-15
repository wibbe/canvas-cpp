
function paint() {
   var ctx = window.getContext('2d');
   ctx.clear();
   ctx.fillStyle = 'rgb(255, 100, 50)';
   ctx.globalAlpha = 0.5;
   ctx.fillRect(10, 10, 100, 100);
}

(function() {
   window.log("Starting Demo...");
   window.setInterval(paint);
})();

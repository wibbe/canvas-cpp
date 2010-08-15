
function paint() {
   var ctx = window.getContext('2d');
   
   ctx.fillStyle = 'rgb(255, 100, 50)';
   ctx.fillRect(10, 10, 100, 100);
}

(function() {
   window.log("Starting Demo...");
   window.setInterval(paint);
})();

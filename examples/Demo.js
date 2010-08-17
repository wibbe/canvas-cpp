
function paint() {
   var ctx = window.getContext('2d');
   ctx.clear();
   ctx.fillStyle = 'rgb(255, 100, 50)';
   ctx.globalAlpha = 0.5;
   ctx.fillRect(10, 10, 100, 100);
   
   ctx.drawImage(window.getImage("examples/logo.png"), 120, 10, 128, 64);
}

(function() {
   console.log("Starting Demo...");
   window.setInterval(paint);
   
   var img = window.getImage("examples/logo.png");
   if (!img)
      console.log("Could not find image 'examples/logo.png'");
   else
      console.log("Image: (" + img.width + "x" + img.height + ")");
})();

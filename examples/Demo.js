
(function() {
   console.log("Starting Demo...");
   
   var ctx = window.getContext('2d');
   var img = window.getImage("examples/logo.png");
   
   if (ctx && img)
      window.setInterval(paint);
      
   function paint() {
      ctx.clear();
      ctx.fillStyle = 'rgb(255, 100, 50)';
      ctx.globalAlpha = 0.5;
      ctx.fillRect(10, 10, 100, 100);
   
      ctx.drawImage(img, 120, 10);
      
      ctx.beginPath();
      ctx.moveTo(200, 200);
      ctx.lineTo(300, 200);
      ctx.lineTo(350, 350);
      ctx.closePath();
      
      ctx.strokeStyle = 'white';
      ctx.lineWidth = 10.0;
      ctx.lineCap = 'round';
      ctx.stroke();
   }
})();

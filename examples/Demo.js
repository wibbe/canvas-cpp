
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
      ctx.drawImage(img, 120, 74, 64, 32);
      
      ctx.beginPath();
      ctx.moveTo(200, 200);
      ctx.lineTo(300, 200);
      ctx.quadraticCurveTo(300, 300, 200, 300);
      
      ctx.rect(700, 10, 90, 90);
      
      ctx.closePath();
      
      ctx.strokeStyle = 'white';
      ctx.lineWidth = 10.0;
      ctx.lineCap = 'round';
      ctx.stroke();
   }
})();

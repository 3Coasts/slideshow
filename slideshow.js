(function ($) {


Drupal.behaviors.slideshow = {
  attach: function (context, settings) {
    $("#slideshow").gallerify();
  }
}


jQuery.fn.gallerify = function() {
    return this.each(function(){

      var id = Math.floor(Math.random()*100000);
      var items = $('li ',this);
      var obj = this;
      var ratio;

      items.css({ 'display':'none' });

      $(items[0]).css({ 'display':'block' });

      if (items.length > 1) {
        $(this).before('<div class="gallery_changer"><ul id="g'+id+'"></ul></div>');
        var changer = $('#g'+id);
        items.each(function(){
          var numberLink = (items.index(this)+1).toString();
          if (numberLink.length == 1) numberLink = '0' + numberLink;
          $('<li><a href="#">'+numberLink+'</a></li>').click(showImage).appendTo(changer);
        });
        $('li:first',changer).addClass('first current');
        $('li:last',changer).addClass('last');

      }

      var auto;
      var current = 0;
      var max = $(items).length -1;

      autotoggle('on');
      $(obj).parents(".block").hover(function(){ 
        autotoggle('off'); 
      }, function(){ 
        autotoggle('on'); 
      });

      function autotoggle(state){
        if(state == 'on'){
          clearInterval(auto);
          auto = setInterval(function(){
            if(current < max){ current++; }else{ current=0; }
            $(obj).parent().find('.gallery_changer li')[current].click();
          },5000);
        }else{
          clearInterval(auto);
        }
      }

      function showImage() {

        var $clicked = $(items[$(this).index()]);
        var $current = $(items[$(this).parent().children('li.current').index()]);

        if($clicked.index() != $current.index()){
          $current.fadeOut();
          $clicked.fadeIn();
          $(this).addClass('current').siblings().removeClass('current');
        }
        return false;
      }

  });
}


}(jQuery));

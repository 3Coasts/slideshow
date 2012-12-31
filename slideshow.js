(function ($) {


Drupal.behaviors.slideshow = {
	attach: function (context, settings) {
		$("#slideshow").gallerify();
	}
}


jQuery.fn.gallerify = function() {
    return this.each(function(){

      id = Math.floor(Math.random()*100000);

      var items = $('li ',this);

      $(this).css({
      	'position':'relative',
      	'width':$(items[0]).width(),
      	'height':$(items[0]).height(),
      })

      items.css({
      	'opacity':0,
      	"z-index":"1",
      	'position':'absolute',
      });

      $(items[0]).css({
      	'opacity':1,
      	"z-index":"3"
      });

      if (items.length > 1) {
        $(this).after('<div class="gallery_changer"><ul id="g'+id+'"></ul></div>');
        var changer = $('#g'+id);
        items.each(function(){
          var numberLink = (items.index(this)+1).toString();
          if (numberLink.length == 1) numberLink = '0' + numberLink;
          $('<li><a href="#">'+numberLink+'</a></li>').click(showImage).appendTo(changer);
        });
        $('li:first',changer).addClass('first current');
        $('li:last',changer).addClass('last');

	    $('.gallery_changer').css({
	    	'position':'relative',
	    	'z-index':10
	    });
      }


      function showImage() {

        var $clicked = $(items[$(this).index()]);
        var $current = $(items[$(this).parent().children('li.current').index()]);

        $clicked.parent().animate({'width':$clicked.width(), 'height': $clicked.height()});
        $current.css({"z-index":"2"});
        $clicked.css({"z-index":"3"}).animate({opacity:1},400, function(){
          $current.css({"opacity":"0","z-index":"1"});
        });

        $(this).addClass('current').siblings().removeClass('current');

        return false;
      }
  });
}


}(jQuery));

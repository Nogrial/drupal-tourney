(function($) {
  Drupal.behaviors.highlightRoundrobin = {
    attach: function(context, settings) {
      $('div.contestant[class*=eid]', context).hover(function() {

        // Contestant divs declare the entity they represent with a CSS class.
        // Grab that class.
        var highlight = $(this).attr('class').match(/\beid-.*\b/);

        if (highlight) {
          
          // Highlight the team's appearances and flow lines. If this is the
          // last time they appear, they probably lost. Don't highlight the
          // flow lines for that.
          $('div.' + highlight).addClass('bracket-highlight')
            .not(':last').closest('div.match-contestant').find('div.flow').addClass('bracket-highlight');
        }
      },
      function() {
        // Remove the highlight on hover out
        $('.bracket-highlight').removeClass('bracket-highlight');
      });
    }
  };
})(jQuery);
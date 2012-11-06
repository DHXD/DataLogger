
  
  (function ($) {

      /*
      Drupal.behaviors.datalogger = {
        attach: function (context, settings) {
          $('fieldset#edit-submit-command-fieldset--8', context).change(function () {
          
              alert('Handler for .change() called.');
              
          });
        }
      };*/
      
      
      setTimeout('datalogger_auto_refresh()', 3000);
      
      function datalogger_auto_refresh() {
      
        var nid_command = 0;    // lay trong HTML ra

        alert('goi ajax refresh...');
    
        $.ajax({
          url: "/datalogger/command/refresh/ajax/" + nid_command,
          context: document.body
        }).done(function( data ) { 
          $('fieldset#edit-submit-command-fieldset--8', this).html(data);
        });
        
      }

    }(jQuery));
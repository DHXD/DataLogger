/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * Navigation Behavior
 */
Drupal.openlayers.addBehavior('openlayers_behavior_navigation', function (data, options) {
  options.documentDrag = !!options.documentDrag;
  Drupal.openlayers.addControl(data.openlayers, 'Navigation', options);
});
;
/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * Javascript Drupal Theming function for inside of Popups
 *
 * To override
 *
 * @param feature
 *  OpenLayers feature object.
 * @return
 *  Formatted HTML.
 */
Drupal.theme.prototype.openlayersPopup = function(feature) {
  var output = '';
  
  if (feature.attributes.name) {
    output += '<div class="openlayers-popup openlayers-tooltip-name">' + feature.attributes.name + '</div>';
  }
  if (feature.attributes.description) {
    output += '<div class="openlayers-popup openlayers-tooltip-description">' + feature.attributes.description + '</div>';
  }
  
  return output;
};

// Make sure the namespace exists
Drupal.openlayers.popup = Drupal.openlayers.popup || {};

/**
 * OpenLayers Popup Behavior
 */
Drupal.openlayers.addBehavior('openlayers_behavior_popup', function (data, options) {
  var map = data.openlayers;
  var layers = [];

  // For backwards compatiability, if layers is not
  // defined, then include all vector layers
  if (typeof options.layers == 'undefined' || options.layers.length == 0) {
    layers = map.getLayersByClass('OpenLayers.Layer.Vector');
  }
  else {
    for (var i in options.layers) {
      var selectedLayer = map.getLayersBy('drupalID', options.layers[i]);
      if (typeof selectedLayer[0] != 'undefined') {
        layers.push(selectedLayer[0]);
      }
    }
  }

  var popupSelect = new OpenLayers.Control.SelectFeature(layers,
    {
      onSelect: function(feature) {
        // Create FramedCloud popup.
        popup = new OpenLayers.Popup.FramedCloud(
          'popup',
          feature.geometry.getBounds().getCenterLonLat(),
          null,
          Drupal.theme('openlayersPopup', feature),
          null,
          true,
          function(evt) {
            Drupal.openlayers.popup.popupSelect.unselect(
              Drupal.openlayers.popup.selectedFeature
            );
          }
        );

        // Assign popup to feature and map.
        feature.popup = popup;
        feature.layer.map.addPopup(popup);
        Drupal.attachBehaviors();
        Drupal.openlayers.popup.selectedFeature = feature;
      },
      onUnselect: function(feature) {
        // Remove popup if feature is unselected.
        feature.layer.map.removePopup(feature.popup);
        feature.popup.destroy();
        feature.popup = null;
      }
    }
  );

  map.addControl(popupSelect);
  popupSelect.activate();
  Drupal.openlayers.popup.popupSelect = popupSelect;
});
;
/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * ZoomPanel Behavior
 */
Drupal.openlayers.addBehavior('openlayers_behavior_zoompanel', function (data, options) {
  Drupal.openlayers.addControl(data.openlayers, 'ZoomPanel');
});
;
/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * Zoom Box Behavior
 */
Drupal.openlayers.addBehavior('openlayers_behavior_zoombox', function (data, options) {
  Drupal.openlayers.addControl(data.openlayers, 'ZoomBox');
});
;
/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * Layer Switcher Behavior
 */
Drupal.openlayers.addBehavior('openlayers_behavior_layerswitcher', function (data, options) {
  options.ascending = !! options.ascending;
  Drupal.openlayers.addControl(data.openlayers, 'LayerSwitcher', options);
});
;
/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * Permalink Behavior
 */
Drupal.openlayers.addBehavior('openlayers_behavior_permalink', function (data, options) {
  Drupal.openlayers.addControl(data.openlayers, 'Permalink', options);
});
;
/**
 * @file
 * JS Implementation of OpenLayers behavior.
 */

/**
 * DragPan Behavior.  Implements the DragPan OpenLayers
 * Control.
 */
Drupal.openlayers.addBehavior('openlayers_behavior_dragpan', function (data, options) {
  Drupal.openlayers.addControl(data.openlayers, 'DragPan', options);
});
;
/**
 * @file
 * OpenLayers Behavior implementation for clustering.
 */

/**
 * OpenLayers Cluster Behavior.
 */
Drupal.openlayers.addBehavior('openlayers_behavior_cluster', function (data, options) {
  var map = data.openlayers;
  var distance = parseInt(options.distance, 10);
  var threshold = parseInt(options.threshold, 10);
  var layers = [];
  for (var i in options.clusterlayer) {
    var selectedLayer = map.getLayersBy('drupalID', options.clusterlayer[i]);
    if (typeof selectedLayer[0] != 'undefined') {
      layers.push(selectedLayer[0]);
    }
  }

  // Go through chosen layers
  for (var i in layers) {
    var layer = layers[i];
    // Ensure vector layer
    if (layer.CLASS_NAME == 'OpenLayers.Layer.Vector') {
      var cluster = new OpenLayers.Strategy.Cluster(options);
      layer.addOptions({ 'strategies': [cluster] });
      cluster.setLayer(layer);
      cluster.features = layer.features.slice();
      cluster.activate();
      cluster.cluster();
    }
  }
});

/**
 * Override of callback used by 'popup' behaviour to support clusters
 */
Drupal.theme.openlayersPopup = function (feature) {
  if (feature.cluster) {
    var output = '';
    var visited = []; // to keep track of already-visited items
    for (var i = 0; i < feature.cluster.length; i++) {
      var pf = feature.cluster[i]; // pseudo-feature
      if (typeof pf.drupalFID != 'undefined') {
        var mapwide_id = feature.layer.drupalID + pf.drupalFID;
        if (mapwide_id in visited) continue;
        visited[mapwide_id] = true;
      }
      output += '<div class="openlayers-popup openlayers-popup-feature">' +
        Drupal.theme.prototype.openlayersPopup(pf) + '</div>';
    }
    return output;
  }
  else {
    return Drupal.theme.prototype.openlayersPopup(feature);
  }
};
;

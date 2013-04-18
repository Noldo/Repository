<?php

/**
 *
 */
define('NAME', 'noldo');
define('GEONAMES_FREE_SERVER_URL', 'http://api.geonames.org/');
/**
*geonames api config
*
*/
function geonames_config() {
  $config['search'] = array(
    'service_name'        => 'search',
    'service_full_name'   => 'GeoNames Fulltext Search',
    'description'         => t('Search provides names and information for geographical locations, it is probably the most comprehensive search available from GeoNames and has numereous possible parameter combinations. Note that this service allows some parameters to be arrays: country, featureclass and featurecode.'),
    'allowed_parameters' => array(
      // our style     // geonames style
      'query'        => 'q',
      'name'         => 'name',
      'name_equals'  => 'name_equals',
      'maxrows'      => 'maxRows',
      'startrow'     => 'startRow',
      'country'      => 'country',
      'admincode1'   => 'adminCode1',
      'admincode2'   => 'adminCode2',
      'admincode3'   => 'adminCode3',
      'featureclass' => 'featureClass',
      'featurecode'  => 'featureCode',
      'lang'         => 'lang',
      'style'        => 'style',
    ),
  );
  $config['postalCodeLookupJSON'] = array(
    'service_name'        => 'postalCodeLookupJSON',
    'service_full_name'   => 'Postal Code Country Info',
    'description'         => 'Find countries for which postal code geocoding is available.',
    'allowed_parameters'  => array(
	  'postalcode',
      'country',
	  'maxRows',
    ),
  );
  $config['children'] = array(
    'service_name'        => 'children',
    'service_full_name'   => 'Place Hierarchy: Children',
    'description'         => t('Find the children of a given geonameId.'),
    'allowed_parameters'  => array(
      // our style        // geonames style
      'geonameid' => 'geonameId',
      'style'     => 'style',
      'maxrows'   => 'maxRows',
      'lang'      => 'lang',
    ),
    'required_parameters' => array(
      'geonameid',
    ),
    );
  $config['countrycode'] = array(
    'service_name'        => 'countrycode',
    'service_full_name'   => 'Country Code (reverse geocoding)',
    'description'         => t('Find Country Code from latitude and longitude'),
    'allowed_parameters'  => array(
      //our style  geonames style
      'lat'      => 'lat',
      'lng'      => 'lng',
      'lang'     => 'lang',
      'type'     => 'type',
    ),
    'required_parameters' => array( // If you have set query_defaults you should not include the parameter here
      'lat',
      'lng'
    ),
    );
  $config['countryinfo'] = array(
    'service_name'        => 'countryinfo',
    'service_full_name'   => 'Country Info (Bounding Box, Capital, Area in square km, Population)',
    'description'         => 'Find countries for which postal code geocoding is available.',
    'allowed_parameters' => array(
      //our style  geonames style
      'country' => 'country',
      'lang' => 'lang',
    ),
    
  );
  $config['countrysubdivision'] = array(
    'service_name'        => 'countrysubdivision',
    'service_full_name'   => 'Country Subdivision (reverse geocoding)',
    'description'         => t('Find Country Code from latitude and longitude'),
    'allowed_parameters'  => array(
      //our style  geonames style
      'lat'      => 'lat',
      'lng'      => 'lng',
      'lang'     => 'lang',
    ),
    'required_parameters' => array( // If you have set query_defaults you should not include the parameter here
      'lat',
      'lng'
    ),
    );
  $config['get'] = array(
    'service_name'        => 'get',
    'service_full_name'   => 'Get',
    'description'         => 'Retrieve GeoNames record by geonameid',
    'allowed_parameters'  => array(
      'geonameid' => 'geonameId',
      'lang'      => 'lang',
    ),
    'columns' => array(
      'geoname',
    ),
  );
  $config['gtopo30'] = array(
    'service_name'             => 'gtopo30',
    'service_full_name'        => 'Elevation - GTOPO30',
    'description'              => t('GTOPO30 is a global digital elevation model (DEM) with a horizontal grid spacing of 30 arc seconds (approximately 1 kilometer). GTOPO30 was derived from several raster and vector sources of topographic information.'),
    'allowed_parameters'       => array(
      //our style  geonames style
      'lat'      => 'lat',
      'lng'      => 'lng',
      'type'     => 'type',
    ),
    'required_parameters'      => array( // If you have set query_defaults you should not include the parameter here
      'lat',
      'lng'
    ),
    );
  $config['hierarchy'] = array(
    'service_name'        => 'hierarchy',
    'service_full_name'   => 'Place Hierarchy: Hierarchy',
    'description'         => t('Find all Geonames higher up in the hierarchy of a place name.'),
    'allowed_parameters'  => array(
      // our style     // geonames style
      'geonameid'         => 'geonameId',
      'style'             => 'style',
      'lang'              => 'lang',
    ),
    'required_parameters' => array(
      'geonameid',
    ),
	);
  $config['findNearby'] = array(
    'service_name'        => 'findNearby',
    'service_full_name'   => 'Find Nearby (reverse geocoding)',
    'description'         => t('Find Nearby (reverse geocoding)'),
    'allowed_parameters'  => array(
      //our style  geonames style
      'lat'               => 'lat',
      'lng'               => 'lng',
      'radius'            => 'radius',
      'featureclass'      => 'featureClass',
      'featurecode'       => 'featureCode',
      'maxrows'           => 'maxRows',
      'style'             => 'style',
    ),
    'array_parameters' => array(
      'featurecode',
      'featureclass',
    ),
    'required_parameters' => array(
      'lat',
      'lng'
    ),
   );
  $config['findNearbyPlaceName'] = array(
    'service_name'             => 'findNearbyPlaceName',
    'service_full_name'        => 'Find nearby Place Name (reverse geocoding)',
    'description'              => t('Find nearby place name (reverse geocoding)'),
    'allowed_parameters'       => array(
      //our style  geonames style
      'lat'      => 'lat',
      'lng'      => 'lng',
      'radius'   => 'radius',
      'maxrows'  => 'maxRows',
      'style'    => 'style',      // Default = MEDIUM
    ),
    'query_defaults' => array(
      'radius' => 20
    ),
    'required_parameters'      => array( // If you have set query_defaults you should not include the parameter here
      'lat',
      'lng'
    ),
    );
  $config['findNearbyPostalCodes'] = array(
    'service_name'        => 'findNearbyPostalCodes',
    'service_full_name'   => 'Find nearby Postal Codes (reverse geocoding)',
    'description'         => 'Find nearby Postal Codes (reverse geocoding)',
    'allowed_parameters' => array(
      //our style  geonames style
      'lat'        => 'lat',
      'lng'        => 'lng',
      'radius'     => 'radius',
      'postalcode' => 'postalcode',
      'maxrows'    => 'maxRows',       // Geonames default = 5
      'country'    => 'country',       // Geonames default = ALL
      'style'      => 'style',
    ),
    'required_parameters' => array( // If you have set query_defaults you should not include the parameter here
      array('lat', 'lng'),
      array('postalcode', 'country')
    ),
    );
  $config['nearbywikipedia'] = array(
    'service_name'        => 'nearbywikipedia',
    'service_full_name'   => 'Find nearby Wikipedia Entries (reverse geocoding)',
    'description' => 'Find nearby Wikipedia Entries (reverse geocoding)',
    'allowed_parameters'  => array(
      //our style  geonames style
      'lat'        => 'lat',
      'lng'        => 'lng',
      'radius'     => 'radius',
      'postalcode' => 'postalcode',
      'lang'       => 'lang',          // Geonames default = en
      'maxrows'    => 'maxRows',       // Geonames default = 5
      'country'    => 'country',       // Geonames default = ALL
    ),
    'required_parameters' => array( // If you have set query_defaults you should not include the parameter here
      array('lat', 'lng'),
      array('postalcode', 'country')
    ),
    );
  $config['neighbours'] = array(
    'service_name'        => 'neighbours',
    'service_full_name'   => 'Place Hierarchy: Neighbours',
    'description'     => t('Returns the neighbours for a given geonameId.'),
    'allowed_parameters'  => array(
      // our style     // geonames style
      'geonameid'       => 'geonameId',
      'style'           => 'style',
      'lang'            => 'lang',
    ),
    'required_parameters' => array(
      'geonameid',
    ),
    );
  $config['postalcodesearch'] = array(
    'service_name'        => 'postalcodesearch',
    'service_full_name'   => 'Postal Code Search',
    'description'         => t('Postalcode search provides placenames/postalcodes for locations.'),
    'allowed_parameters' => array(
      // our style     // geonames style
      'postalcode'  => 'postalcode',
      'placename'   => 'placename',
      'maxrows'     => 'maxRows',
      'style'       => 'style',
      'country'     => 'country',    // if not set -- all countries
    ),
    'required_parameters' => array( // If you have set query_defaults you should not include the parameter here
      'postalcode',
      'placename',
    ),
  );
  $config['siblings'] = array(
    'service_name'        => 'siblings',
    'service_full_name'   => 'Place Hierarchy: Siblings',
    'description'         => t('Returns the siblings for a given geonameId.'),
    'allowed_parameters'  => array(
      // our style     // geonames style
      'geonameid'         => 'geonameId',
      'style'             => 'style',
      'lang'              => 'lang',
    ),
    'required_parameters' => array(
      'geonameid',
    ),
    );
  $config['srtm3'] = array(
    'service_name'             => 'srtm3',
    'service_full_name'        => 'Elevation - SRTM3',
    'description'              => t('Shuttle Radar Topography Mission (SRTM) elevation data. The dataset covers land areas between 60 degrees north and 56 degrees south. This web service is using SRTM3 data with data points located every 3-arc-second (approximately 90 meters) on a latitude/longitude grid. Result: a single number giving the elevation in meters according to srtm3, ocean areas have been masked as "no data" and have been assigned a value of -32768'),
    'allowed_parameters'       => array(
      //our style  geonames style
      'lat'      => 'lat',
      'lng'      => 'lng',
      'type'     => 'type',
    ),
    'required_parameters'      => array( // If you have set query_defaults you should not include the parameter here
      'lat',
      'lng'
    ),
  );
  $config['timezone'] = array(
    'service_name'             => 'timezone',
    'service_full_name'        => 'Timezone',
    'description'              => t('Find the timezone for a given lat/lng with gmt offset (1. January) and dst offset (1. July)'),
    'allowed_parameters'       => array(
      //our style  geonames style
      'lat'      => 'lat',
      'lng'      => 'lng',
    ),
    'required_parameters'      => array( // If you have set query_defaults you should not include the parameter here
      'lat',
      'lng'
    ),
  );
  $config['wikipediabbox'] = array(
    'service_name'        => 'wikipediabbox',
    'service_full_name'   => 'Wikipedia Articles from Bounding Box',
    'description'         => 'Search Wikipedia entries within the Bounding Box',
    'allowed_parameters' => array(
      //our style  geonames style
      'north'      => 'north',
      'south'      => 'south',
      'east'       => 'east',
      'west'       => 'west',
      'lang'       => 'lang',
      'maxrows'    => 'maxRows',
    ),
    'required_parameters' => array( // If you have set query_defaults you should not include the parameter here
      'north',
      'south',
      'east',
      'west',
    ),
    );
  $config['wikipediasearch'] = array(
    'service_name'        => 'wikipediasearch',
    'service_full_name'   => 'Wikipedia Fulltext Search',
    'description'         => 'Search Wikipedia entries in Fulltext',
    'allowed_parameters' => array(
      //our style  geonames style
      'query'      => 'q',
      'title'      => 'title',
      'lang'       => 'lang',          // Geonames default = en
      'maxrows'    => 'maxRows',       // Geonames default = 5
    ),
    'required_parameters' => array( // If you have set query_defaults you should not include the parameter here
      array('query'),
      // array('title'),
    ),
    );
  $config['cities'] = array(
    'service_name'        => 'cities',
    'service_full_name'   => 'Cities and Placenames',
    'description'         => 'returns a list of cities and placenames in the bounding box, ordered by relevancy (capital/population)',
    'allowed_parameters' => array(
      //our style  geonames style
      'north'      => 'north',
      'south'      => 'south',
      'east'       => 'east',
      'west'       => 'west',
      'lang'       => 'lang',
      'maxrows'    => 'maxRows',
    ),
    'required_parameters' => array( // If you have set query_defaults you should not include the parameter here
      'north',
      'south',
      'east',
      'west',
    ),
  );
  $config['findNearbyStreets'] = array(
    'service_name'             => 'findNearbyStreets',
    'service_full_name'        => 'Find nearby Streets',
    'description'              => t('Finds the nearest street for a given lat/lng pair.'),
    'allowed_parameters'       => array(
      //our style  geonames style
      'lat'      => 'lat',
      'lng'      => 'lng',
    ),
    'required_parameters'      => array( // If you have set query_defaults you should not include the parameter here
      'lat',
      'lng'
    ),
    );
  $config['findNearestIntersection'] = array(
    'service_name'             => 'findNearestIntersection',
    'service_full_name'        => 'Find nearest Intersection',
    'description'              => t('Finds the nearest street and the next crossing street for a given lat/lng pair.'),
    'allowed_parameters'       => array(
      //our style  geonames style
      'lat'      => 'lat',
      'lng'      => 'lng',
    ),
    'required_parameters'      => array( // If you have set query_defaults you should not include the parameter here
      'lat',
      'lng'
    ),
    );
  $config['findNearestAddress'] = array(
    'service_name'             => 'findNearestAddress',
    'service_full_name'        => 'Find nearest Address',
    'description'              => t('Find nearest Address'),
    'allowed_parameters'       => array(
      //our style  geonames style
      'lat'      => 'lat',
      'lng'      => 'lng',
    ),
    'required_parameters'      => array( // If you have set query_defaults you should not include the parameter here
      'lat',
      'lng'
    ),
    );
  $config['neighbourhood'] = array(
    'service_name'             => 'neighbourhood',
    'service_full_name'        => 'Neighbourhood / reverse geocoding',
    'description'              => t('The neighbourhood for US cities. Data provided by Zillow under cc-by-sa license.'),
    'allowed_parameters'       => array(
      //our style  geonames style
      'lat'      => 'lat',
      'lng'      => 'lng',
    ),
    'required_parameters'      => array( // If you have set query_defaults you should not include the parameter here
      'lat',
      'lng'
    ),
    );
  $config['findNearByWeather'] = array(
    'service_name'             => 'findNearByWeather',
    'service_full_name'        => 'Weather Station with most recent weather observation / reverse geocoding',
    'description'              => t('returns a weather station with the most recent weather observation'),
    'allowed_parameters'       => array(
      //our style  geonames style
      'lat'      => 'lat',
      'lng'      => 'lng',
    ),
    );
  $config['ocean'] = array(
    'service_name'             => 'ocean',
    'service_full_name'        => 'Ocean / reverse geocoding',
    'description'              => t('The name of the ocean or sea.'),
    'allowed_parameters'       => array(
      //our style  geonames style
      'lat'      => 'lat',
      'lng'      => 'lng',
    ),
    'required_parameters'      => array( // If you have set query_defaults you should not include the parameter here
      'lat',
      'lng'
    ),
    );
  $config['extendedFindNearby'] = array(
    'service_name'             => 'extendedFindNearby',
    'service_full_name'        => 'Extended Find nearby toponym / reverse geocoding',
    'description'              => t('returns the most detailed information available for the lat/lng query.'),
    'allowed_parameters'       => array(
      //our style  geonames style
      'lat'      => 'lat',
      'lng'      => 'lng',
    ),
    'required_parameters'      => array( // If you have set query_defaults you should not include the parameter here
      'lat',
      'lng'
    ),
    );
  $config['astergdem'] = array(
    'service_name'             => 'astergdem',
    'service_full_name'        => 'Elevation - Aster Global Digital Elevation Model',
    'description'              => t('a single number giving the elevation in meters according to aster gdem.'),
    'allowed_parameters'       => array(
      //our style  geonames style
      'lat'      => 'lat',
      'lng'      => 'lng',
    ),
    'required_parameters'      => array( // If you have set query_defaults you should not include the parameter here
      'lat',
      'lng'
    ),
    );
  return $config;
}

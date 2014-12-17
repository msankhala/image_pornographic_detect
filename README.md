### Image pornographic detect

A simple drupal module which allow site administor to configure image field to not allow pornographic image upload.
This module uses two thrid party librarries:
- [Php nudity detector](https://github.com/FreebieStock/php-nudity-detector)
- [Image nudity filter](http://www.phpclasses.org/package/3269-PHP-Determine-whether-an-image-may-contain-nudity.html)
Admin interface of module allow which library to use for pornographic detection.

##### @todo
Porn image detect for user profile.

Dependencies:
[Libraries API](https://www.drupal.org/project/libraries)

**Steps**


- Download and extract module under `sites/all/modules`
- Download and extract `Libraries` module.
- Download one of the library or both.
  - [Php nudity detector](https://github.com/FreebieStock/php-nudity-detector) (recommended)
  - [Image nudity filter](http://www.phpclasses.org/package/3269-PHP-Determine-whether-an-image-may-contain-nudity)
- Extract and put the library under `sites/all/libraries/` and make sure path is `sites/all/libraries/php-nudity-detector` (for php nudity detector library) and `sites/all/libraries/image-nudity-filter` (for Image nudity filter library).
- Enable the module and configure any `image field` added in content type and check the pornograhpic detection option.
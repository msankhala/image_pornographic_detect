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

Steps
-----

- Download and extract module under `sites/all/modules`
- Download and extract `Libraries` module.
- Download one of the library or both.
  - [Php nudity detector](https://github.com/FreebieStock/php-nudity-detector) (recommended)
  - [Php nudity detector](https://github.com/FreebieStock/php-nudity-detector)
- Extract and put the library under `sites/all/libraries/
- Enable the module and configure any `image field` added in content type and check the pornograhpic detection option.
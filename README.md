# MoBaGEn
Welcome to the **MoBaGEn**. The **MO**dule **BA**sed **G**ame **EN**gine. 

**MoBaGEn** is a free lightweight, cross-platform 3D Game Engine implemented in C++ and scripted in C#(Mono), Javascript(V8) and Lua.

[![Coverity](https://scan.coverity.com/projects/14798/badge.svg)](https://scan.coverity.com/projects/infinibrains-mobagen) [![Build Status](https://api.travis-ci.org/InfiniBrains/mobagen.svg?branch=master)](https://travis-ci.org/InfiniBrains/mobagen)

## Feature:
- Scene Graph
- 3D model loading (most common file formats)
- Entity/Component Object Model
- Lighting system (ambient/spot/point/directional lights) - Forward rendering
- Bump mapping
- Perspective/Ortho camera
- Object picking (basic ray tracing/sphere collider collision detection)
- Fully cross platform

## License
Licensed under the [![WTFPL](http://www.wtfpl.net/wp-content/uploads/2012/12/wtfpl-badge-4.png)](http://www.wtfpl.net/). In short: you can do whatever you want to do, and we kindly ask you for a contribution to pay our bills. See [LICENSE](LICENSE.md) for details.

## Contributing
Before making pull requests, please read the [Contribution checklist](CONTRIBUTION.md) and [Coding Conventions](CODINGCONVENTION.md) pages from the documentation.

## Branches
We publish source for the engine in three rolling branches:

The **[master branch](https://github.com/InfiniBrains/mobagen/tree/master)** tracks [live changes](https://github.com/InfiniBrains/mobagen/commits/master) by our engine team. 
This is the cutting edge and may be buggy - it may not even compile. Battle-hardened developers eager to work lock-step with us on the latest and greatest should head here.

The **[release branch](https://github.com/InfiniBrains/mobagen/tree/release)** is extensively tested by our QA team and makes a great starting point for learning the engine or making your own games. We work hard to make releases stable and reliable, and aim to publish new releases every few months.

The **_feature_ branch** where _feature_ is the name of a given feature being developed. When it is done, it will merge its differences into the **[master branch](https://github.com/InfiniBrains/mobagen/tree/master)**.

Other short-lived branches may pop-up from time to time as we stabilize new releases or hotfixes.

## Documentation
The documentation is also available online at [Documentation](docs/HEAD/index.html)

Documentation on how to build MoBaGEn: [Building](BUILDING.md)

## History
The change history is available online at [History](docs/HEAD/history.html)

## Third Parties
This project was made using these open-sourced [third parties](THIRDPARTIES.md).

## Contributors
MoBaGEn development is made by these [People](PEOPLE.md), and the top contributors are:
- [Alexandre Tolstenko](linkedin.com/in/aletolstenko/)

## Sponsorship
This project is sponsored via [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=tolstenko@gmail.com) and [Patreon](https://www.patreon.com/tolstenko) by these kind people:
- [Alexandre Tolstenko](http://linkedin.com/in/aletolstenko/)
- Aurus Dourado
- Bruno Aragão
- Joel Oliveira
- Rafael Dalmazo

## Finance Report
In order to report our costs properly via [OpenCollective](https://opencollective.com/) we need to achieve at least 100 stars in this repository. So please star us!

## Development Log
You can see our reports and tutorials via our channel in [YouTube](https://www.youtube.com/tolstenko) or our [Blog](http://infinibrains.com/blog)

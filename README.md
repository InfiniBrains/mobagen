# MoBaGEn
Welcome to the **MoBaGEn**. The **MO**dule **BA**sed **G**ame **EN**gine. 

**MoBaGEn** is a free lightweight, cross-platform 3D Game Engine implemented in C++. It will support scripts in C#(Mono), Javascript(V8), python and Lua.


[![Build status](https://ci.appveyor.com/api/projects/status/5mdt9wslio6fl7vp?svg=true)](https://ci.appveyor.com/project/tolstenko/mobagen) [![Build Status](https://api.travis-ci.org/InfiniBrains/mobagen.svg?branch=master)](https://travis-ci.org/InfiniBrains/mobagen) [![Active Contributors](https://api.gitential.com/accounts/758/projects/809/badges/active-contributors.svg)](https://gitential.com/accounts/758/projects/809/share?uuid=7533eb0d-42e1-41f1-8f8f-a8f8f1fdce70&utm_source=shield&utm_medium=shield&utm_campaign=809) [![Code Volume](https://api.gitential.com/accounts/758/projects/809/badges/code-volume.svg)](https://gitential.com/accounts/758/projects/809/share?uuid=7533eb0d-42e1-41f1-8f8f-a8f8f1fdce70&utm_source=shield&utm_medium=shield&utm_campaign=809) [![Coding Hours](https://api.gitential.com/accounts/758/projects/809/badges/coding-hours.svg)](https://gitential.com/accounts/758/projects/809/share?uuid=7533eb0d-42e1-41f1-8f8f-a8f8f1fdce70&utm_source=shield&utm_medium=shield&utm_campaign=809) [![Efficiency](https://api.gitential.com/accounts/758/projects/809/badges/efficiency.svg)](https://gitential.com/accounts/758/projects/809/share?uuid=7533eb0d-42e1-41f1-8f8f-a8f8f1fdce70&utm_source=shield&utm_medium=shield&utm_campaign=809) [![Utilization](https://api.gitential.com/accounts/758/projects/809/badges/utilization.svg)](https://gitential.com/accounts/758/projects/809/share?uuid=7533eb0d-42e1-41f1-8f8f-a8f8f1fdce70&utm_source=shield&utm_medium=shield&utm_campaign=809) [![Coverity](https://scan.coverity.com/projects/14798/badge.svg)](https://scan.coverity.com/projects/infinibrains-mobagen)  [![Coverage Status](https://coveralls.io/repos/github/InfiniBrains/mobagen/badge.svg?branch=master)](https://coveralls.io/github/InfiniBrains/mobagen?branch=master)
[![Waffle.io - Columns and their card count](https://badge.waffle.io/InfiniBrains/mobagen.svg?columns=all)](https://waffle.io/InfiniBrains/mobagen)
[![Throughput Graph](https://graphs.waffle.io/InfiniBrains/mobagen/throughput.svg)](https://waffle.io/InfiniBrains/mobagen/metrics/throughput)

## Feature:
- Scene Graph
- 3D model loading (most common file formats)
- Entity/Component Object Model (WiP - Migrating to use something similar to Unity3D)
- Lighting system (ambient/spot/point/directional lights) - Forward rendering
- Bump mapping
- Perspective/Ortho camera
- Object picking (basic ray tracing/sphere collider collision detection) (WiP - We plan to integrate bullet physics to do it)
- Fully cross platform - Windows (Tested: Visual Studio, MinGW; Continous integrated: MinGW on linux), HTML5 (via Emscripten), Linux (gcc and clang), Android (NDK, not integrated to CI yet), iOS(WiP - [Planned](https://github.com/InfiniBrains/mobagen/issues/39)), OSX(Xcode and terminal tools).

## License
Licensed under the [![WTFPL](http://www.wtfpl.net/wp-content/uploads/2012/12/wtfpl-badge-4.png)](http://www.wtfpl.net/). In short: you can do whatever you want to do, and we kindly ask you for a contribution to pay our bills. See [LICENSE](LICENSE.md) for details.

## Contributing

[Join us](https://infinibrains-team-inviter.herokuapp.com/) on Slack [![Slack Status](https://infinibrains-inviter.herokuapp.com/badge.svg)](https://infinibrains-team-inviter.herokuapp.com/)!
 
Before making pull requests, please read the [Contribution checklist](CONTRIBUTION.md) and [Coding Conventions](CODINGCONVENTION.md) pages from the documentation.

## Branches
We publish source for the engine in three rolling branches:

The **[master branch](https://github.com/InfiniBrains/mobagen/tree/master)** tracks [release changes](https://github.com/InfiniBrains/mobagen/commits/master) by our engine team. It is extensively tested by our QA team and makes a great starting point for learning the engine or making your own games. We work hard to make releases stable and reliable, and aim to publish new releases every few months.

The **[development branch](https://github.com/InfiniBrains/mobagen/tree/development)** This is the cutting edge and may be buggy - it may not even compile. Battle-hardened developers eager to work lock-step with us on the latest and greatest should head here.

The **_feature_ branch** where _feature_ is the name of a given feature being developed. When it is done, it will merge its differences into the **[master branch](https://github.com/InfiniBrains/mobagen/tree/master)**.

Other short-lived branches may pop-up from time to time as we stabilize new releases or hotfixes.

## Documentation
The documentation is also available online at [Documentation](docs/HEAD/index.html) (Work in Progress. Help Needed.)

Documentation on how to build MoBaGEn: [Building](BUILDING.md)

## History
The change history is available online at [History](docs/HEAD/history.html) (Work in Progress. Help Needed.)

## Third Parties
This project was made using these open-sourced [third parties](THIRDPARTIES.md).

## Contributors
MoBaGEn development is made by these [People](PEOPLE.md), and the top contributors are:
- [Alexandre Tolstenko](http://linkedin.com/in/aletolstenko/)
- [Marcos Soares](http://linkedin.com/in/marcos-soares-391718141/)

## Sponsorship
This project is sponsored via [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=tolstenko@gmail.com) and [Patreon](https://www.patreon.com/tolstenko) by these kind people:
- [Alexandre Tolstenko](http://linkedin.com/in/aletolstenko/)

## Finance Report
In order to report our costs properly via [OpenCollective](https://opencollective.com/) we need to achieve at least 100 stars in this repository. So please star us!

## Development Log
You can see our reports and tutorials via our channel in [YouTube](https://www.youtube.com/tolstenko) or our [Blog](http://infinibrains.com/blog)

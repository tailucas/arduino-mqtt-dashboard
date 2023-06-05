<a name="readme-top"></a>

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

## About The Project

This project is a companion to one of my other projects for [Inverter Monitoring][inverter-monitor-url] and enables [Espressif][esp-url] ESP8266 and ESP32 devices to drive LED displays to act as a basic dashboard, updated via [MQTT][mqtt-url] messages from a network-local broker.

You can find a brief write-up about this project [here](https://tailucas.github.io/update/2023/06/04/inverter-monitoring.html).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

Technologies that help make this package useful:

[![Arduino IDE][arduino-shield]][arduino-ide-url]
[![Espressif][esp-shield]][esp-url]
[![MQTT][mqtt-shield]][mqtt-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

Here is some detail about the intended use of this package.

### Prerequisites

An [Arduino IDE][arduino-ide-url] or equivalent environment to compile and upload the `.ino` sketches.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->
## Usage

The sketches do not currently make use of [WiFiManager](https://github.com/tzapu/WiFiManager) which is tantamount to best practice when building IoT applications. My next update to these projects will make this change, or feel free to send me a pull request.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See [LICENSE](LICENSE) for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* Thank you Marco Colli for the various [MajicDesigns](https://github.com/MajicDesigns) libraries that make these projects work.
* [Template on which this README is based](https://github.com/othneildrew/Best-README-Template)
* [All the Shields](https://github.com/progfay/shields-with-icon)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/tailucas/arduino-mqtt-dashboard.svg?style=for-the-badge
[contributors-url]: https://github.com/tailucas/arduino-mqtt-dashboard/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/tailucas/arduino-mqtt-dashboard.svg?style=for-the-badge
[forks-url]: https://github.com/tailucas/arduino-mqtt-dashboard/network/members
[stars-shield]: https://img.shields.io/github/stars/tailucas/arduino-mqtt-dashboard.svg?style=for-the-badge
[stars-url]: https://github.com/tailucas/arduino-mqtt-dashboard/stargazers
[issues-shield]: https://img.shields.io/github/issues/tailucas/arduino-mqtt-dashboard.svg?style=for-the-badge
[issues-url]: https://github.com/tailucas/arduino-mqtt-dashboard/issues
[license-shield]: https://img.shields.io/github/license/tailucas/arduino-mqtt-dashboard.svg?style=for-the-badge
[license-url]: https://github.com/tailucas/arduino-mqtt-dashboard/blob/main/LICENSE

[inverter-monitor-url]: https://github.com/tailucas/inverter-monitor

[arduino-ide-url]: https://www.arduino.cc/en/Guide
[arduino-shield]: https://img.shields.io/static/v1?style=for-the-badge&message=Arduino&color=00979D&logo=Arduino&logoColor=FFFFFF&label=
[esp-url]: https://www.espressif.com/
[esp-shield]: https://img.shields.io/static/v1?style=for-the-badge&message=Espressif&color=E7352C&logo=Espressif&logoColor=FFFFFF&label=
[mqtt-url]: https://mqtt.org/
[mqtt-shield]: https://img.shields.io/static/v1?style=for-the-badge&message=MQTT&color=660066&logo=MQTT&logoColor=FFFFFF&label=

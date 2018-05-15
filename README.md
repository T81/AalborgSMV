# Aalborg SMV library for Arduino

Controls an [**Aalborg SMV**](http://www.aalborg.com/index.php/main_page/product_overview/id_product_overview/29) stepping motor valve in a matter of speed percentage, closing and purging.

Requires an [**MCP49xx**](https://gr.mouser.com/new/microchip/microchipdacs/#tabs-5) dac for speed control and the [**DAC_MCP49xx**](https://github.com/exscape/electronics/tree/master/Arduino/Libraries/DAC_MCP49xx) arduino library

Currently supported DACs (MCP49xx family):

- [ ] MCP4901 (single, 8-bit)
- [ ] MCP4911 (single, 10-bit)
- [x] MCP4921 (single, 12-bit)
- [ ] MCP4902 (dual, 8-bit)
- [ ] MCP4912 (dual, 10-bit)
- [ ] MCP4922 (dual, 12-bit)
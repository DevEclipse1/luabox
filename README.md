# LuaBox – Mini Gaming Console Firmware

**LuaBox** is a compact mini gaming console powered by the **ESP32**, featuring custom firmware and PCB design. It lets you program games and applications in **Lua**, offering a portable DIY retro gaming experience.  

---

## Showcase


![Showcase](showcase.mp4)


---

---

## Docs
[Documentation available here](https://deveclipse1.github.io/luabox/index.html)

---

---

## Features

- Runs on **ESP32** for efficient performance.  
- **LuaBox firmware**: program games and apps in **Lua**.  
- Open-source and fully documented for hobbyists and developers.  

---

## Pinouts

- You can change the pinout in [The pins file](src/pins.h)
- And for the display pins, change in .pio/libdeps/board/TFT_eSPI/User_Setup.h

---

## SD card setup

- For the firmware to work, you need a SD card connected to the ESP32, and you need to create some folders
- Create a folder called **games** (the .lua games you will see in the main menu) and **assets** (for images, gifs, data)
  
---

## Contributing
- Fork the repo and create your own games or improvements.  
- Keep the project name **LuaBox** intact in your forks.  
- Submit pull requests if you have enhancements or bug fixes.  

---

## License
This project is licensed under the **MIT License**.  
See the [LICENSE](LICENSE) file for details.  

---

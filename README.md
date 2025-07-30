# YPP Shop Manager

A CLI tool to help manage Puzzle Pirates shops.
It simply offers an interactive way to browse through and edit a JSON file containing the recipes and prices.
It is flexible enough so that it can be used for a single shop, for the shops in an island or your whole businesses,
although it has been designed for the management of the shops in a single island in mind.

The most powerful feature is the ability to see both the order price of a recipe and its unit cost.
With it you can easily adjust your prices for direct orders or for dock-side trade.

# Build instructions
## Prerequisites
* A C++ compiler compatible with the C++23 standard. The project is built in both [GCC](https://gcc.gnu.org/) and [CLang](https://clang.llvm.org/).
* [CMake](https://cmake.org/).
* [nlohmann/json](https://github.com/nlohmann/json). There are packages availables for Linux. For Windows, you can try downloading with [Chocolatey](https://chocolatey.org/install).

## Building steps
1. Clone the git repository with `https://github.com/Xaunther/YPP_Shop_Manager.git`.
2. Navigate to the `build` folder (create one if there isn't) and configure the build with `cmake ...`.
3. Build with `cmake --build . -j6`. You may use any other number of threads.

# Running instructions
You can run either the produced or the download binary reading your JSON containing all the recipes and prices that you want to consider with:
```bash
./YPP_Shop_Manager -f <your_json_file>
```
You can try using the provided example in [`tests/unit/blackthorpe.json`](tests/unit/blackthorpe.json).
If you are modifying a JSON file, just remember that the changes are not saved until you select the `Save JSON` option in the main menu.

In the provided JSON example, the recipes are categorized by shop, and the prices by the commodity type.
You can, however, make your own categories if you wish, just keep in mind that everything is sorted alphabetically.


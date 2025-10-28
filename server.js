const express = require("express");
const path = require("path");
const fs = require("fs");

const app = express();
const PORT = 3000;

// 🔧 Map routes to specific files
const routes = {
  fcfs: "fcfs.cpp",
  lru: "lru.cpp",
  readwrite: "readerwriter.cpp",
  rr: "rr.cpp",
  sjf: "sjf.cpp",
  prodcons: "producerconsumer.cpp",
  try: "trycatch.java",
  thread: "ThreadDemo.java",
  tic: "PlayableTicTacToe.java",
  file: "FileHandlingDemo.java",
  pascal: "pascal.py",
  fibonacci: "fibonacci.py",
  calc: "calculator.py",
  dict: "dict.py",
  subdict: "subdict.py",
  list: "list.py",
  array3d: "3darray.py",
};

// 🧱 Serve files based on route name
app.get("/:name", (req, res) => {
  const routeName = req.params.name;
  const fileName = routes[routeName];

  if (!fileName) {
    return res.status(404).send("No such route or file defined!");
  }

  const filePath = path.join(__dirname, fileName);

  if (!fs.existsSync(filePath)) {
    return res.status(404).send("File not found on server!");
  }

  res.sendFile(filePath);
});

// 🚀 Start server
app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});


"use strict";

let GetFacesFromImage = require('./GetFacesFromImage.js')
let DetectObjects = require('./DetectObjects.js')
let GetCubes = require('./GetCubes.js')
let GetThermalAngle = require('./GetThermalAngle.js')
let TrainObject = require('./TrainObject.js')
let RecognizeObject = require('./RecognizeObject.js')
let DetectGripper = require('./DetectGripper.js')
let RecognizeObjects = require('./RecognizeObjects.js')
let FindWaving = require('./FindWaving.js')
let FindLines = require('./FindLines.js')
let FaceRecognition = require('./FaceRecognition.js')
let GetPanoramic = require('./GetPanoramic.js')
let FindPlane = require('./FindPlane.js')

module.exports = {
  GetFacesFromImage: GetFacesFromImage,
  DetectObjects: DetectObjects,
  GetCubes: GetCubes,
  GetThermalAngle: GetThermalAngle,
  TrainObject: TrainObject,
  RecognizeObject: RecognizeObject,
  DetectGripper: DetectGripper,
  RecognizeObjects: RecognizeObjects,
  FindWaving: FindWaving,
  FindLines: FindLines,
  FaceRecognition: FaceRecognition,
  GetPanoramic: GetPanoramic,
  FindPlane: FindPlane,
};

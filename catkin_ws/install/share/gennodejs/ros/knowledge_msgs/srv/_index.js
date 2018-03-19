
"use strict";

let wait_for_command = require('./wait_for_command.js')
let wait_for_switch = require('./wait_for_switch.js')
let ask_store_name = require('./ask_store_name.js')
let planning_cmd = require('./planning_cmd.js')
let search_remember_face = require('./search_remember_face.js')
let parse_sentence_cfr = require('./parse_sentence_cfr.js')
let GetPredefinedArmsPoses = require('./GetPredefinedArmsPoses.js')
let InitKDB = require('./InitKDB.js')
let KnownLocations = require('./KnownLocations.js')
let find_person = require('./find_person.js')
let AddUpdateKnownLoc = require('./AddUpdateKnownLoc.js')
let place_object = require('./place_object.js')
let StrQueryKDB = require('./StrQueryKDB.js')
let wait_for_confirm = require('./wait_for_confirm.js')
let GetPredefinedQuestions = require('./GetPredefinedQuestions.js')

module.exports = {
  wait_for_command: wait_for_command,
  wait_for_switch: wait_for_switch,
  ask_store_name: ask_store_name,
  planning_cmd: planning_cmd,
  search_remember_face: search_remember_face,
  parse_sentence_cfr: parse_sentence_cfr,
  GetPredefinedArmsPoses: GetPredefinedArmsPoses,
  InitKDB: InitKDB,
  KnownLocations: KnownLocations,
  find_person: find_person,
  AddUpdateKnownLoc: AddUpdateKnownLoc,
  place_object: place_object,
  StrQueryKDB: StrQueryKDB,
  wait_for_confirm: wait_for_confirm,
  GetPredefinedQuestions: GetPredefinedQuestions,
};

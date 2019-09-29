String userLuggage[2][2] = { {"Marie", "lug_M"}, {"John", "lug_J"}};

void findLuggageOfUser(String user) {
  //Serial.println(userLuggage);
  for (int j = 0; j <= sizeof(userLuggage); j++) {
    if (userLuggage[j][0] == user) {
      Serial.println(userLuggage[j][1]);
    }
  }
}

#pragma once

struct QueueFamilyIndices {
     int graphicsFamily = -1;

     // Check if the queue families are valid
     bool isComplete() { return graphicsFamily >= 0; }
};
# pragma once

enum OutputState {
    SILENT,
    VIBRATING,
    FULL
};

struct MenuStates {
    OutputState output_state; // Store the output state
    // Add other state variables as needed
    // int someOtherState;
    // bool anotherState;
};
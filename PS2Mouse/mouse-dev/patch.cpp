#pragma XOD require "https://github.com/kristopher/PS2-Mouse-Arduino"


{{#global}}
#include <PS2Mouse.h>
{{/global}}

struct State {
    uint8_t mem[sizeof(PS2Mouse)];
};

using Type = PS2Mouse*;

{{ GENERATED_CODE }}

void evaluate(Context ctx) {
    if (!isSettingUp())
        return;

    auto state = getState(ctx);

    Type mouse = new (state->mem) PS2Mouse(getValue<input_Clock>(ctx),getValue<input_Data>(ctx),getValue<input_Mode>(ctx));
    mouse->initialize()
    emitValue<output_Dev>(ctx, mouse);
}

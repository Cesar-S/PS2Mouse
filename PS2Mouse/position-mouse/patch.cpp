struct State {
};

{{ GENERATED_CODE }}

void evaluate(Context ctx) {

    if (!isInputDirty<input_Get>(ctx)){
    emitValue<output_Dev>(ctx, getValue<input_PS2>(ctx));
        return;}

    auto mouse = getValue<input_PS2>(ctx);
    uint8_t stat;
    int x,y;
    mouse->getPosition(uint8_t &stat, int &x, int &y);
    emitValue<output_X_Value>(ctx, x);
    emitValue<output_Y_Value>(ctx, y);
    emitValue<output_Done>(ctx, 1);
    emitValue<output_Dev>(ctx, mouse);

}

struct State {
};

{{ GENERATED_CODE }}

void evaluate(Context ctx) {

    if (!isInputDirty<input_Get>(ctx)){
    emitValue<output_Dev>(ctx, getValue<input_PS2>(ctx));
        return;}

    auto mouse = getValue<input_PS2>(ctx);
    bool scaling = getValue<input_Scaling>(ctx);
    if(scaling == true){
        mouse->set_scaling_1_1();
    }else{
        mouse->set_scaling_2_1();
    }
    emitValue<output_Done>(ctx, 1);
    emitValue<output_Dev>(ctx, mouse);

}

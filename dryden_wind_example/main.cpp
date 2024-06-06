// coding: GBK
//dryden紊流强度修改在wenliu_data.cpp第57行，2U代表robability of exceedance of high-altitude intensity 是10e-2
//如果要调整时间步长，需要同步修改dryden中的时间步长，在wenliu.cpp第130行和841行
//如果时间步长为0.0001，则第130行 >999；如果时间步长为0.001，则第130行>99
//如果时间步长为0.0001，则第841行 =0.0001；如果时间步长为0.001，则第841行 =0.001

#include <stdio.h>  // This example main program uses printf/fflush
#include "wenliu.h" // Model header file
#include <iostream> // This example main program uses cout/cin
#include "rt_logging.h"
#ifndef SAVEFILE
#define MATFILE2(file) #file ".mat"
#define MATFILE1(file) MATFILE2(file)
#define MATFILE MATFILE1(MODEL)
#else
#define QUOTE1(name) #name
#define QUOTE(name) QUOTE1(name) // need to expand name
#define MATFILE QUOTE(SAVEFILE)
#endif

static wenliu model; // Instance of model class

void rt_OneStep(void);
void rt_OneStep(void)
{
    static boolean_T OverrunFlag{false};

    // Disable interrupts here

    // Check for overrun
    if (OverrunFlag)
    {
        rtmSetErrorStatus(model.getRTM(), "Overrun");
        return;
    }

    OverrunFlag = true;

    // Save FPU context here (if necessary)
    // Re-enable timer or interrupt here
    // Set model inputs here

    // Step the model
    model.step();

    // Get model outputs here

    // Indicate task complete
    OverrunFlag = false;

    // Disable interrupts here
    // Restore FPU context here (if necessary)
    // Enable interrupts here
}

int_T main()
{
    double v_dry_x = 0.0;
    double v_dry_y = 0.0;
    double v_dry_z = 0.0;

    //double v_dry[3] = {0.0, 0.0, 0.0};

    wenliu::ExtY_wenliu_T output;

    model.initialize();

    wenliu::ExtU_wenliu_T inputs = {5000.0, 108.0}; // Create input structure

    model.setExternalInputs(&inputs); // Set model inputs

    for (int i = 0; i < 2000; i++)
    {
        rt_OneStep();
        output = model.getExternalOutputs(); // Get the output
        v_dry_x = output.Vx;
        v_dry_y = output.Vy;
        v_dry_z = output.Vz;
        printf("The output is: %f %f %f\n", v_dry_x, v_dry_y, v_dry_z); // Display the output

    }




    model.terminate();

    return 0;
}
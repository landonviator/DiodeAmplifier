/*
  ==============================================================================

    CabButtonProps.cpp
    Created: 6 Jul 2021 6:08:27pm
    Author:  Landon Viator

  ==============================================================================
*/

#include "PluginEditor.h"

void DiodeAmplifierAudioProcessorEditor::setCabButtonProps()
{
    
    cabButton.setClickingTogglesState(false);
    
    cabButton.onClick = [&]()
    {
        juce::FileChooser chooser ("Select an impulse response", {}, "*");
                
        if (chooser.browseForFileToOpen())
        {
            if (chooser.getResult().getFileExtension() == ".wav" || chooser.getResult().getFileExtension() == ".mp3")
            {
                audioProcessor.savedFile = chooser.getResult();
                
                audioProcessor.variableTree.setProperty("file", audioProcessor.savedFile.getFullPathName(), nullptr);

                audioProcessor.convolutionProcessor.loadImpulseResponse(audioProcessor.savedFile, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0);
                        
                DBG(audioProcessor.savedFile.getFullPathName());
            }
        
            else
            {
                settingsDialog.showNativeDialogBox("Error", "The file you chose is unsupported in some way. Select a .wav or .mp3 file.", false);
            }
        }
    };
}

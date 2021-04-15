class SvLightData {
  public:
    // Constructor inits everything to NULL
    SvLightData();
    
    SoSceneViewer   *classPt;
    SoSwitch	    *lightSwitch;
    SoTranslation   *translation;   // for placing a directional light manip
    SoScale         *scale;
    SoLight	    *light;
    SoScale         *scaleInverse;
    SoTranslation   *translationInverse;
    SoType	    type;
    char	    *name;
    SoMfcColorEditor *colorEditor;
    SbBool     	    isManip;
    SbBool     	    shouldBeManip; // Used to remember what it was when
				   // they all get turned off for writing,
				   // printing, etc.

	// these two are to help out with light dialog state
	SbBool iconON;
	SbBool lightON;

};



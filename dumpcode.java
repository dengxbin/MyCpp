public ExposureInfo(CaptureResult result) {
    mAntibandingMode = result.get(CaptureResult.CONTROL_AE_ANTIBANDING_MODE); //all
    mCompensation = result.get(CaptureResult.CONTROL_AE_EXPOSURE_COMPENSATION); //all
    mLocked = result.get(CaptureResult.CONTROL_AE_LOCK); //all
    mMode = result.get(CaptureResult.CONTROL_AE_MODE); //all
    // partial result sometimes doesn't have flash mode but the request always has it
    // so get it from the request
    mFlashMode = result.getRequest().get(CaptureRequest.FLASH_MODE);
    mPrecaptureTrigger = result.get(CaptureResult.CONTROL_AE_PRECAPTURE_TRIGGER); //limited
    mState = result.get(CaptureResult.CONTROL_AE_STATE); //limited
    mFlashState = result.get(CaptureResult.FLASH_STATE); //limited
    mTargetFpsRange = result.get(CaptureResult.CONTROL_AE_TARGET_FPS_RANGE); //all
    int hwLevel = SettingsHelper.getHardwareLevel();
    mIsValid = mAntibandingMode != null && mCompensation != null && mLocked != null &&
            mMode != null && mTargetFpsRange != null &&
            (hwLevel != CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL_LEGACY  &&
                    mPrecaptureTrigger != null && mState != null);
} 
ExposureStateMachine: ExposureInfo isn't valid: ExposureInfo
{mMode=1, mCompensation=null, mAntibandingMode=null, mPrecaptureTrigger=null, mState=2, mFlashState=null, mLocked=null, mTargetFpsRange=null, mIsValid=false}


     * <p>AE is off or recently reset.</p>
3142       * <p>When a camera device is opened, it starts in
3143       * this state. This is a transient state, the camera device may skip reporting
3144       * this state in capture result.</p>
3145       * @see CaptureResult#CONTROL_AE_STATE
3146       */
3147      public static final int CONTROL_AE_STATE_INACTIVE = 0;
3148  
3149      /**
3150       * <p>AE doesn't yet have a good set of control values
3151       * for the current scene.</p>
3152       * <p>This is a transient state, the camera device may skip
3153       * reporting this state in capture result.</p>
3154       * @see CaptureResult#CONTROL_AE_STATE
3155       */
3156      public static final int CONTROL_AE_STATE_SEARCHING = 1;
3157  
3158      /**
3159       * <p>AE has a good set of control values for the
3160       * current scene.</p>
3161       * @see CaptureResult#CONTROL_AE_STATE
3162       */
3163      public static final int CONTROL_AE_STATE_CONVERGED = 2;
3164  
3165      /**
3166       * <p>AE has been locked.</p>
3167       * @see CaptureResult#CONTROL_AE_STATE
3168       */
3169      public static final int CONTROL_AE_STATE_LOCKED = 3;
3170  
3171      /**
3172       * <p>AE has a good set of control values, but flash
3173       * needs to be fired for good quality still
3174       * capture.</p>
3175       * @see CaptureResult#CONTROL_AE_STATE
3176       */
3177      public static final int CONTROL_AE_STATE_FLASH_REQUIRED = 4;
3178  
3179      /**
3180       * <p>AE has been asked to do a precapture sequence
3181       * and is currently executing it.</p>
3182       * <p>Precapture can be triggered through setting
3183       * {@link CaptureRequest#CONTROL_AE_PRECAPTURE_TRIGGER android.control.aePrecaptureTrigger} to START. Currently
3184       * active and completed (if it causes camera device internal AE lock) precapture
3185       * metering sequence can be canceled through setting
3186       * {@link CaptureRequest#CONTROL_AE_PRECAPTURE_TRIGGER android.control.aePrecaptureTrigger} to CANCEL.</p>
3187       * <p>Once PRECAPTURE completes, AE will transition to CONVERGED
3188       * or FLASH_REQUIRED as appropriate. This is a transient
3189       * state, the camera device may skip reporting this state in
3190       * capture result.</p>
3191       *
3192       * @see CaptureRequest#CONTROL_AE_PRECAPTURE_TRIGGER
3193       * @see CaptureResult#CONTROL_AE_STATE
3194       */
3195      public static final int CONTROL_AE_STATE_PRECAPTURE = 5;
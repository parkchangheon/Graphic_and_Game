using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

using Coffee.UIEffects;
public class CutScene : MonoBehaviour
{
    Dictionary<string,CutSceneConfiguration> configurations = new Dictionary<string, CutSceneConfiguration>();

    [SerializeField]
    List<CutSceneConfiguration> cutSceneConfigurations;

    CutSceneConfiguration currentConfiguration;

    [SerializeField]
    List<string> cutSceneNames;

    [SerializeField]
    Image image;

    [SerializeField]
    Text narration;

    UITransitionEffect uiEffect;

    bool isClick = false;

    private void Awake()
    {
        narration.gameObject.SetActive(true);
        if (cutSceneConfigurations.Count != cutSceneNames.Count)
        {
            Debug.LogError("CutScene.cs :: currentConfiguration DATA_COUNT_ERROR");
            return;
        }

        for(int i = 0; i < cutSceneConfigurations.Count; i++)
        {
            configurations.Add(cutSceneNames[i],cutSceneConfigurations[i]);
        }

    }
    private void Start()
    {
        uiEffect = image.GetComponent<UITransitionEffect>();
        

        StartCutScene(SceneTransition.instance.GetCutScenename());
    }

    public void StartCutScene(string cutScene_name)
    {
       if(configurations.ContainsKey(cutScene_name))
       {
            if(cutScene_name.Contains("lose"))
            {
                SoundMgr.instance.PlayBGM("Gameover");
            }
            else if (cutScene_name.Contains("clear"))
            {
                
                     SoundMgr.instance.PlayBGM("Ending");
            }
            else
            {
                SoundMgr.instance.PlayBGM("cutsceneBGM");
            }
            




            currentConfiguration = configurations[cutScene_name];
       }
       else
       {
            Debug.LogError("CutScene.cs :: cutScene_name ERROR");
            return;
       }

        StartCoroutine(ChangeImage());

    }
    Coroutine coroutine = null;
    IEnumerator ChangeImage()
    {
        yield return new WaitForSeconds(0.5f);

        for (int i = 0; i < currentConfiguration.sprites.Count; i++)
        {
            image.sprite = currentConfiguration.sprites[i];
            narration.text = currentConfiguration.narration[i];
            uiEffect.effectFactor = 0.0f;
            uiEffect.Show(false);

            if(coroutine != null)
            {
                StopCoroutine(coroutine);
                coroutine = null;
            }

            coroutine = StartCoroutine(TextAnimation(narration.text.Length * 0.06f));

            yield return new WaitForSeconds(uiEffect.effectPlayer.duration);

            while(isClick == false)
                yield return null;
            isClick = false;


            if(i == currentConfiguration.sprites.Count-1)
            {
                SceneTransition.instance.GetAction().Invoke();
            }
        }
    }

    IEnumerator TextAnimation(float duration)
    {
        string _text = narration.text;
        for (int i = 0; i <= _text.Length; i ++)
        {
            narration.text = _text.Substring(0, i);
            yield return new WaitForSeconds(duration / (float)_text.Length);
        }
    }


    public void OnClick()
    {
        isClick = true;
    }

    public void Skip()
    {
        SceneTransition.instance.GetAction().Invoke();
    }

}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIManager :MonoBehaviour// : MonoSingleton<UIManager>
{
    [SerializeField]
    GameObject pausePopupObj = null;

    public Move_Player player;

    public Text timerUIText;
    public Timer timer;


    public Image Gauge;

    public Text dashCoolTime;

    private void Update()
    {
        timerUIText.text = timer.GetTiemStr();
        Gauge.fillAmount = GameManager.gm.Gauge_Amount();

        if (player.dashCoolTime < 0f)
        {
            //dashCoolTime.text = "0s";
            dashCoolTime.enabled = false;
        }
        else
        {
            dashCoolTime.text = string.Format("{0}s", (int)player.dashCoolTime);
            dashCoolTime.enabled = true;
        }


    }





    public void SetPausePopup(bool active)
    {
        pausePopupObj.SetActive(active);
    }

}

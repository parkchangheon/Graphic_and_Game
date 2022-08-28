using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreScript : MonoBehaviour
{

    public Text myScoreText;
    public static int ScoreNum;
    // Start is called before the first frame update
    void Start()
    {
        ScoreNum = 0;
        myScoreText.text = "score : " + ScoreNum;
    }
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.collider.CompareTag("Item"))
        {
            Debug.Log("asdasdasd");
            ScoreNum += 1;
            myScoreText.text = "score : " + ScoreNum;
        }
        
    }

}

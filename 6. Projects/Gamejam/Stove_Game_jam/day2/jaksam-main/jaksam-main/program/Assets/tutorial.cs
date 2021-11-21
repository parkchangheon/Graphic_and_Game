using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class tutorial : MonoBehaviour
{
    public int index = 1;
    public Sprite[] sprites;
    public SpriteRenderer spriteRenderer;
    float cooltime = 0.0f;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        cooltime -= Time.deltaTime;
        if (cooltime < 0 && Input.GetMouseButtonDown(0))
        {
            cooltime = 1f;
            index++;

            if(index > sprites.Length)
            {
                SceneManager.LoadScene("GameScene");
                return;
            }

            spriteRenderer.sprite = sprites[index -1];
        }
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class dash : MonoBehaviour
{
    public SpriteRenderer spriteRenderer;

    private void Start()
    {
        spriteRenderer = this.GetComponent<SpriteRenderer>();
        Color c = spriteRenderer.color;
        c.a = 1;
        spriteRenderer.color = c;
        StartCoroutine("stop");
    }

    IEnumerator stop()
    {
        while(true)
        {
            Color c = spriteRenderer.color;
       
            if(c.a < 0.1)
            {
                break;
            }

            Color cc = new Color(0, 0, 0, 1);
            spriteRenderer.color -= cc * Time.deltaTime;
            yield return new WaitForEndOfFrame();
        }

        Destroy(this.gameObject);
    }

    // Update is called once per frame
    void Update()
    {

    }
}

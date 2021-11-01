using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SubFoodObject : MonoBehaviour
{
    public float speed = 5f;
    FoodObject parentObject;
    public bool endDestroy = true;
    public float destroyTime = 1f;
    public void Set(FoodObject foodObject)
    {
        parentObject = foodObject;
    }

    private void Update()
    {
        //두번째 파라미터에 Space.World를 해줌으로써 Rotation에 의한 방향 오류를 수정함
        transform.Translate(Vector2.right * speed * Time.deltaTime, Space.Self);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.CompareTag("Player"))
        {
            GameManager.gm.SetGuage(parentObject.healthGauge);

            if(parentObject.foodType == FOOD_TYPE.JUNK)
            {
                CameraShake.cs.Shake(0.5f);
            }

            if(endDestroy)
                Destroy(this.gameObject);
        }
    }


}

#include "stdafx.h"

Scene01::Scene01()
{
    LIGHT->light.radius = 2000.0f;
    pl = new Player();

    weapon = new Weapon();
    
    pickAxe = new PickAxe();
    pickAxe->GearOff();

    sword = new Sword();
    sword->GearOff();
    
    torch = new Torch();


    bags = new Bag();
    screenUI = new OnScreen();

    for (int y = 0; y < bagY; y++)
    {
        for (int x = 0; x < bagX; x++)
        {
            icons[x][y] = new Icon();
        }
    }
    icons[0][0]->AddItem(ItemType::WEAPON);


    //mon = new Monster();
    map = new ObTileMap();
    map->file = "map1.txt";
    map->Load();
    //map->CreateTileCost();
    //
    //m.lock();
    //Sleep(1000);
    //loadingCount++;
    //m.unlock();
    //m.lock();
    //Sleep(1000);
    //loadingCount++;
    //m.unlock();
    //m.lock();
    //Sleep(1000);
    //loadingCount++;
    //m.unlock();
    //m.lock();
    //Sleep(1000);
    //loadingCount++;
    //m.unlock();
    //m.lock();
    //Sleep(1000);
    //loadingCount++;
    //m.unlock();
    //

    /*m.lock();
    Sleep(1000);
    loadingCount++;
    m.unlock();
    m.lock();
    Sleep(1000);
    loadingCount++;
    m.unlock();
    m.lock();
    Sleep(1000);
    loadingCount++;
    m.unlock();
    m.lock();
    Sleep(1000);
    loadingCount++;
    m.unlock();
    
    m.lock();
    Sleep(1000);
    loadingCount++;
    m.unlock();*/
}

Scene01::~Scene01()
{
    SafeDelete(pl);
    //SafeDelete(mon);
    //SafeDelete(map);
}

void Scene01::Init()
{
}

void Scene01::Release()
{
}

void Scene01::Update()
{
    //ImGui::SliderFloat2("Scale", (float*)&map->scale, 0.0f, 100.0f);

    if (INPUT->KeyDown('Q'))
    {
        icons[0][0]->AddItem(ItemType::WEAPON);
    }



    if (INPUT->KeyDown(VK_TAB))
    {
        isOpenBag = !isOpenBag;
    }

    torch->GetPlayer(pl->GetPos());

    pickAxe->SetTarget(pl->GetPos());
    sword->SetTarget(pl->GetPos());

    //icons�� Type�� ���������� bag�� ������Ʈ ���ֱ�
    for (int y = 0; y < bagY; y++)
    {
        for (int x = 0; x < bagX; x++)
        {
            bags->SetBagitemType(x, y, icons[x][y]->GetItem());
        }
    }

    if (!isOpenBag)
    {
        for (int x = 0; x < bagX; x++)
        {
            icons[x][0]->SetIconPos(bags->GetHotbarPos(x));
        }
    }
    else
    {
        for (int y = 0; y < bagY; y++)
        {
            for (int x = 0; x < bagX; x++)
            {
                icons[x][y]->SetIconPos(bags->GetBagitemPos(x, y));
            }
        }
    }



   for (int x = 0; x < bagX; x++)
   {
       if (bags->ReturnCol()->Intersect(bags->ReturnHotbarCol(x)))
       {

           if (bags->GetBagitemType(x , 0) == ItemType::WEAPON)
           {
               bags->AddItem(bags->GetBagitemType(x, 0));
               sword->GearOn();
               pickAxe->GearOff();
               torch->GearOff();
           }
           else if (bags->GetBagitemType(x, 0) == ItemType::TOOL)
           {
               bags->AddItem(bags->GetBagitemType(x, 0));
               pickAxe->GearOn();
               sword->GearOff();
               torch->GearOff();
           }
           else if (bags->GetBagitemType(x, 0) == ItemType::TORCH)
           {
               bags->AddItem(bags->GetBagitemType(x, 0));
               torch->GearOn();
               sword->GearOff();
               pickAxe->GearOff();
           }
           else if (bags->GetBagitemType(x, 0) == ItemType::NONE)
           {
               bags->AddItem(bags->GetBagitemType(x, 0));
               sword->GearOff();
               pickAxe->GearOff();
               torch->GearOff();
           }
       }
   }

   screenUI->SetItemType(bags->GetItemType());


    //��Ŭ��������
    //if (INPUT->KeyDown(VK_RBUTTON))
    //{
    //    //   �����, ������
    //    Int2 sour, dest;
    //    //ã�Ҵ°�?
    //    bool isFind;
    //
    //    isFind = map->WorldPosToTileIdx(pl->GetPos(), sour);
    //    isFind &= map->WorldPosToTileIdx(INPUT->GetMouseWorldPos(), dest);
    //
    //    //�Ѵ� Ÿ�ϸ� ����������
    //    if (isFind)
    //    {
    //        //���� �����Ѵٸ�
    //        if (map->PathFinding(sour, dest, PlWay))
    //        {
    //            //�� �����ŭ �ݺ�
    //            for (int i = 0; i < PlWay.size(); i++)
    //            {
    //                cout << "Way" << i << ":" << PlWay[i]->idx.x <<
    //                    "," << PlWay[i]->idx.y << endl;
    //            }
    //            g = 0.0f;
    //            PlSour = pl->GetPos();
    //            PlWay.pop_back(); //����� ����
    //            PlDest = PlWay.back()->Pos;
    //        }
    //
    //    }
    //
    //}
    //
    //���ߵ� ���� ������ ��
    //if (!PlWay.empty())
    //{
    //    //PlSour = pl->GetPos();
    //    pl->SetPos(Utility::Lerp(PlSour, PlDest, g));
    //    g += DELTA * 3.0f;
    //
    //    //�������� ��������
    //    if (g > 1.0f)
    //    {
    //        g = 0.0f;
    //        PlSour = PlDest;
    //        PlWay.pop_back(); //�ǵޱ� ����
    //        if (!PlWay.empty())
    //            PlDest = PlWay.back()->Pos;
    //    }
    //}

    pl->Update();

    pickAxe->Update();
    sword->Update();
    torch->Update();

    bags->Update();
    screenUI->Update();

    for (int y = 0; y < bagY; y++)
    {
        for (int x = 0; x < bagX; x++)
        {
            icons[x][y]->Update();
        }
    }

    //mon->SetTarget(pl->GetPos());
    //mon->Update();
    map->Update();

    CAM->position = pl->GetPos();
}

void Scene01::LateUpdate()
{
    //INPUT->GetMouseWorldPos()








    //if (torch->isInterSect(sword->ReturnHitBox()))
    //{
    //    cout << "�̰ŵ�?" << endl; //��!!!!
    //}

    if (sword->ReturnHitBox()->Intersect(torch->ReturnCol()))
    {
        //cout << "�̰ǵ�?" << endl;  //��!!!!
        sword->attackCoolTime();
        torch->GetPlayer(pl->GetPos());
        torch->GetHiBox(pl->ReturnColBox());

        torch->count--;
    }


    //Int2 on;
    //
    //if (map->WorldPosToTileIdx(pl->GetPos(), on))
    //{
    //    ImGui::Text("TileState %d", map->GetTileState(on));
    //}
    //
    //vector<Vector2>& Foot = pl->GetFoot();
    //
    //for (int i = 0; i < 4; i++)
    //{
    //    Int2 on;
    //    if (map->WorldPosToTileIdx(Foot[i], on))
    //    {
    //        if (map->GetTileState(on) == TILE_WALL)
    //        {
    //            pl->StepBack();
    //        }
    //    }
    //}


}

void Scene01::Render()
{
    //                               L  T   R   B
    //DWRITE->RenderText(L"�ȳ�\n�ȳ�", RECT{ 300,100,(long)app.GetWidth(),(long)app.GetHalfHeight() },
    //    30.0f, L"�޸ո���ü", Color(1, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);


    //map->Render();

    
    if (sword->GetWeaponDir() == 2)
    {
        //pickAxe->Render();
        sword->Render();
        torch->Render();
        pl->Render();
    }
    else
    {
        pl->Render();
        //pickAxe->Render();
        sword->Render();
        torch->Render();
    }

    //mon->Render();



    bags->Render();
    screenUI->Render();


    if (!isOpenBag)
    {
        for (int x = 0; x < bagX; x++)
        {
            icons[x][0]->Render();
        }
    }
    else
    {
        for (int y = 0; y < bagY; y++)
        {
            for (int x = 0; x < bagX; x++)
            {
                icons[x][y]->Render();
            }
        }
    }

    //for (int y = 0; y < bagY; y++)
    //{
    //    for (int x = 0; x < bagX; x++)
    //    {
    //        icons[x][y]->Render();
    //    }
    //}
}

void Scene01::ResizeScreen()
{
}
